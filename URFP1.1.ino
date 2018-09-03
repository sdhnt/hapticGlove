const int motorControl1 = 10;
const int motorControl2 = 9;

int inOutValue1[8];
int inOutValue2[8];


const int selectPinsOutMux1[3] = {11,12,13}; // S0~2, S1~3, S2~4
const int selectPinsOutMux2[3] = {6,7,8}; 

const int selectPinsInpMux1[3] = {0,1,2};
const int selectPinsInpMux2[3] = {3,4,5};
const int zInputMux1 = A1; // Connect common (Z) to A0 (analog input)
const int zInputMux2 = A0; // Connect common (Z) to A0 (analog input)


void setup() {


  pinMode(motorControl1, OUTPUT);  
  pinMode(motorControl2, OUTPUT);  
  
  for (int i=0; i<3; i++)
  {
    pinMode(selectPinsOutMux1[i], OUTPUT);
    digitalWrite(selectPinsOutMux1[i], LOW);
  }

  for (int i=0; i<3; i++)
  {
    pinMode(selectPinsOutMux2[i], OUTPUT);
    digitalWrite(selectPinsOutMux2[i], LOW);
  }

  Serial.begin(9600); // Initialize the serial port
  // Set up the select pins as outputs:
  for (int i=0; i<3; i++)
  {
    pinMode(selectPinsInpMux1[i], OUTPUT);
    digitalWrite(selectPinsInpMux1[i], HIGH);
    pinMode(selectPinsInpMux2[i], OUTPUT);
    digitalWrite(selectPinsInpMux2[i], HIGH);
  }
  pinMode(zInputMux1, INPUT); // Set up Z as an input
  pinMode(zInputMux2, INPUT); // Set up Z as an input

  // Print the header:
  Serial.print("Y0\tY1\tY2\tY3\tY4\tY5\tY6\tY7 ");
  Serial.println("Y0\tY1\tY2\tY3\tY4\tY5\tY6\tY7");
  Serial.print("---\t---\t---\t---\t---\t---\t---\t--- ");
  Serial.println("---\t---\t---\t---\t---\t---\t---\t---");
  
}


void loop() {
  
     for (byte pin=0; pin<=7; pin++)
  {
    selectMuxPin1(pin); // Select one at a time
    inOutValue1[pin] = analogRead(zInputMux1); // and read Z for Input MUX 1
    Serial.print(String(inOutValue1[pin]) + "\t");
    delay(1);
  }

  delay(1);
  Serial.print(" ");
    for (byte pin=0; pin<=7; pin++)
  {
    selectMuxPin2(pin); // Select one at a time
    inOutValue2[pin] = analogRead(zInputMux2); // and read Z for Input MUX 1
    Serial.print(String(inOutValue2[pin]) + "\t");
    delay(1);
  }
  Serial.println();

  
    for (byte pin=0; pin<=7; pin++)
  {
    selectMuxPin1(pin); // Select one at a time
    analogWrite(motorControl1, map(inOutValue1[pin], 0, 1023, 0, 255));//MAP IT ALSO
    selectMuxPin2(pin); // Select one at a time
    analogWrite(motorControl2,  map(inOutValue2[pin], 0, 1023, 0, 255));
    delay(1);
  }
  
}



void selectMuxPin1(byte pin)
{
  if (pin > 7) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPinsOutMux1[i], HIGH);
    else
      digitalWrite(selectPinsOutMux1[i], LOW);
  }
}

void selectMuxPin2(byte pin)
{
  if (pin > 7) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPinsOutMux2[i], HIGH);
    else
      digitalWrite(selectPinsOutMux2[i], LOW);
  }
}
