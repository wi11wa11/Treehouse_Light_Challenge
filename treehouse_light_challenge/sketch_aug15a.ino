//-------Treehouse light challenge------------
//------William Wallis s3773723--------------
//------Electronic prototyping Aug 2022------


//LED and button variables
int ledPin = 2; //LED pin
int buttonPin = 12; //buttonpin
int buttonState = 0; //variable to determine if button has been pressed


//photoresistor variables
int photPin = 4; //photoresistor pin
#define CHN 0 //define the pwm channel 
#define FRQ 1000 //define the pwm frequency
#define PWM_BIT 8 //define the pwm precision
int lightVal; // variable to store photoresistor light value CHANGE VARIABLE TYPE


//motion detector variables
int pirPin = 14; //PIR (Passive Infra-Red) sensor pin
int pirState = 0; //variable to determine if motion is detected


//bluetooth connectivity variables
#include "BluetoothSerial.h" // this header is needed for Bluetooth Serial
BluetoothSerial ESP_BT; //initialises class?? not sure what this does :/
int incomingData; //variable for reading the incoming data over bluetooth


void setup() {
  pinMode(ledPin, OUTPUT); //configures the LedPin to output, as we are sending info out to the pin
  pinMode(buttonPin, INPUT); //configures buttonPin to input, as we are using the button state to control the LED
  pinMode(photPin, INPUT); //configures photoresistor pin to input
  pinMode(pirPin, INPUT); //configures PIR pin to input

  ledcSetup(CHN, FRQ, PWM_BIT); //setup pwm channel
  ledcAttachPin(ledPin, CHN); //attach the led pin to pwm channel

  Serial.begin(9600);
  ESP_BT.begin("ESP32_Control!!!!!😉😇"); //name of bluetooth device on phone
}


void loop() {
  buttonState = digitalRead(buttonPin); // read the value of the pushbutton as either a 1 (on) or 0 (off)
  lightVal = analogRead(photPin); //reads light value
  lightVal = map(lightVal, 0, 4095, 0, 255); //maps light value to 0 - 255
  pirState = digitalRead(pirPin); //reads the state of the PIR sensor
  Serial.println(lightVal); //printed light photoresistor values --- used to configure light level of when light can be turned on 

  if (pirState == 1) {
    Serial.println("motion detected wow so good!!!!!!!⭐💖⭐"); //prints text to monitor if motion is detected
  }

  if (buttonState == 1 || pirState == 1 && lightVal > 170) { //if statement, if the light is low AND the button has been pressed OR motion has been recognized, run code
    ledcWrite(CHN, 255); //using PWM to turn LED on at max brightness
    delay(135000); //wait 2 minutes 15 seconds before continuing statement (135000 milliseconds)(CHANGE TO TEST CODE)
    for (int i = 255; i > -1; i--) { //for loop counting backwards from 255 (max brightness) to -1 (no brightness/off) (fade LED)
      ledcWrite(CHN, i); //writing the i value to the LED brightness
      delay(10); //delaying the for loop to make the fade out smoother over more time
    }
    delay(1000); //little delay idk
  } 

  if (ESP_BT.available()) { //checks if bluetooth device is available
    incomingData = ESP_BT.read(); //read what is recieved from bluetooth device

    Serial.println("LIGHT BUTTON DATA 😃😃"); //if we get some data prints this
    Serial.println(incomingData); //prints the incoming data value

    if (incomingData == 1) { 
      ledcWrite(CHN, 255); //using PWM to turn LED on at max brightness
    } else {
      ledcWrite(CHN, 0); 
    }
  }
}

//--------------------------------------------thank for reading 👍😎😃😍😌
