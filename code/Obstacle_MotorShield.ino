#include <Adafruit_MotorShield.h>

#define trigPin 2 // define the pins of your sensor
#define echoPin 3
#define EN 9
#define IN1 8
#define IN2 7

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);// set up motors.
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);
//Setup Motor A (front and rear) pins
int enableA = 1;
int pinA1 = 3;
int pinA2 = 2;

//Setup Motor B (front and rear) pins
int enableB = 6;
int pinB1 = 5;
int pinB2 = 4; 
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // begin serial communication
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);// set the trig pin to output (Send sound waves)
  pinMode(echoPin, INPUT);// set the echo pin to input (recieve sound waves)
  motor1->setSpeed(105);
  motor2->setSpeed(105);
  motor3->setSpeed(105);
  motor4->setSpeed(105);

  pinMode (enableA, OUTPUT);
  pinMode (pinA1, OUTPUT);
  pinMode (pinA2, OUTPUT);

  pinMode (enableB, OUTPUT);
  pinMode (pinB1, OUTPUT);
  pinMode (pinB2, OUTPUT);

  //turn motors on
  digitalWrite(enableA, HIGH);
  digitalWrite(enableB, HIGH); 

}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;// convert the distance to centimeters.

  if (distance < 25) { //if there's an obstacle 25 centimeters ahead, do the following:
    Serial.println ("Close Obstacle detected!" );
    Serial.println ("Obstacle Details:");
    Serial.print ("Distance From Robot is ");
    Serial.print (distance + " cm");
    Serial.println ("The obstacle is declared a threat due to close distance.");
    Serial.println ("Turning!");
    avoid();
  } else {
    Serial.println ("No obstacle detected, going forward");
    delay(15);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
  }
}

void forward(int duration) {
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(duration);
}

void backwards(int duration) {
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
  delay(duration);
}

void right(int duration) {
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(duration);
}

void avoid() {
  backwards(500);
  right(360);
} 

