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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ LOW ; 
 scalar_t__ NOT_A_PIN ; 
 scalar_t__ NOT_ON_TIMER ; 
 scalar_t__ SREG ; 
 int /*<<< orphan*/  cli () ; 
 scalar_t__ digitalPinToBitMask (scalar_t__) ; 
 scalar_t__ digitalPinToPort (scalar_t__) ; 
 scalar_t__ digitalPinToTimer (scalar_t__) ; 
 scalar_t__* portOutputRegister (scalar_t__) ; 
 int /*<<< orphan*/  turnOffPWM (scalar_t__) ; 

void digitalWrite(uint8_t pin, uint8_t val)
{
	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

	if (port == NOT_A_PIN) return;

	// If the pin that support PWM output, we need to turn it off
	// before doing a digital write.
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	out = portOutputRegister(port);

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

	SREG = oldSREG;
}