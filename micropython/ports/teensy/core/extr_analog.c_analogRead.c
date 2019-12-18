#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
 int ADC0_RA ; 
 int ADC0_SC1A ; 
 int /*<<< orphan*/  ADC1_CFG2 ; 
 int ADC1_RA ; 
 int ADC1_SC1A ; 
 int /*<<< orphan*/  ADC_CFG2_MUXSEL ; 
 int ADC_SC1_COCO ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __enable_irq () ; 
 int analogReadBusyADC0 ; 
 int analogReadBusyADC1 ; 
 int analog_right_shift ; 
 scalar_t__ calibrating ; 
 int* channel2sc1a ; 
 int /*<<< orphan*/  wait_for_cal () ; 
 int /*<<< orphan*/  yield () ; 

int analogRead(uint8_t pin)
{
	int result;
	uint8_t index, channel;

	//serial_phex(pin);
	//serial_print(" ");

	if (pin <= 13) {
		index = pin;      // 0-13 refer to A0-A13
	} else if (pin <= 23) {
		index = pin - 14; // 14-23 are A0-A9
#if defined(__MK20DX256__)
	} else if (pin >= 26 && pin <= 31) {
		index = pin - 9;  // 26-31 are A15-A20
#endif
	} else if (pin >= 34 && pin <= 40) {
		index = pin - 24;  // 34-37 are A10-A13, 38 is temp sensor,
			    // 39 is vref, 40 is unused (A14 on Teensy 3.1)
	} else {
		return 0;   // all others are invalid
	}

	//serial_phex(index);
	//serial_print(" ");

	channel = channel2sc1a[index];
	//serial_phex(channel);
	//serial_print(" ");

	//serial_print("analogRead");
	//return 0;
	if (calibrating) wait_for_cal();
	//pin = 5; // PTD1/SE5b, pin 14, analog 0

#if defined(__MK20DX256__)
	if (channel & 0x80) goto beginADC1;
#endif

	__disable_irq();
startADC0:
	//serial_print("startADC0\n");
	ADC0_SC1A = channel;
	analogReadBusyADC0 = 1;
	__enable_irq();
	while (1) {
		__disable_irq();
		if ((ADC0_SC1A & ADC_SC1_COCO)) {
			result = ADC0_RA;
			analogReadBusyADC0 = 0;
			__enable_irq();
			result >>= analog_right_shift;
			return result;
		}
		// detect if analogRead was used from an interrupt
		// if so, our analogRead got canceled, so it must
		// be restarted.
		if (!analogReadBusyADC0) goto startADC0;
		__enable_irq();
		yield();
	}

#if defined(__MK20DX256__)
beginADC1:
	__disable_irq();
startADC1:
	//serial_print("startADC0\n");
	// ADC1_CFG2[MUXSEL] bit selects between ADCx_SEn channels a and b.
	if (channel & 0x40) {
		ADC1_CFG2 &= ~ADC_CFG2_MUXSEL;
	} else {
		ADC1_CFG2 |= ADC_CFG2_MUXSEL;
	}
	ADC1_SC1A = channel & 0x3F;
	analogReadBusyADC1 = 1;
	__enable_irq();
	while (1) {
		__disable_irq();
		if ((ADC1_SC1A & ADC_SC1_COCO)) {
			result = ADC1_RA;
			analogReadBusyADC1 = 0;
			__enable_irq();
			result >>= analog_right_shift;
			return result;
		}
		// detect if analogRead was used from an interrupt
		// if so, our analogRead got canceled, so it must
		// be restarted.
		if (!analogReadBusyADC1) goto startADC1;
		__enable_irq();
		yield();
	}
#endif
}