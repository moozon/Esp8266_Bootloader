/*
    Name:       Esp8266_Bootloader.ino
    Created:	12.09.2019 11:36:50
    Author:     SRV\admin
*/
#define APP_START_ADR 0x00001000

// Button Defines
#define BUTTON_PIN D3
#define BUTTON_PIN2 D7
// Interrupt Button Define
//#define INTERRUPT_PIN D7

//bool keyPressed = false;
//bool prevState = LOW;

typedef uint32_t appJumpAdrT;
appJumpAdrT appJumpAdr = *((volatile uint32_t*)(APP_START_ADR));


typedef void(*jumpToAppT) (void);

jumpToAppT jumpToApp = (void (*) (void))appJumpAdr;
bool ledState = false;
uint8_t cnt = 0;

void setup()
{
	Serial.begin(115200);
	delay(10);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);

	if (!digitalRead(BUTTON_PIN)) {
		jumpToApp();
		//Serial.println("This");
		//delay(500);
		//return;
	}	
}

void loop()
{	
	if (cnt == 2) {
		ledState = !ledState;
		digitalWrite(LED_BUILTIN, ledState);
		cnt = 0;
	}
	cnt++;
	Serial.println("This is Bootloader");	
	delay(500);
}
