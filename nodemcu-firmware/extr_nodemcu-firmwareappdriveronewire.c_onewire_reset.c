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
 int /*<<< orphan*/  DIRECT_MODE_INPUT (scalar_t__) ; 
 int /*<<< orphan*/  DIRECT_READ (scalar_t__) ; 
 int /*<<< orphan*/  DIRECT_WRITE_LOW (scalar_t__) ; 
 int /*<<< orphan*/  delayMicroseconds (int) ; 
 int /*<<< orphan*/  interrupts () ; 
 int /*<<< orphan*/  noInterrupts () ; 

uint8_t onewire_reset(uint8_t pin)
{
	uint8_t r;
	uint8_t retries = 125;

	noInterrupts();
	DIRECT_MODE_INPUT(pin);
	interrupts();
	// wait until the wire is high... just in case
	do {
		if (--retries == 0) return 0;
		delayMicroseconds(2);
	} while ( !DIRECT_READ(pin));

	noInterrupts();
	DIRECT_WRITE_LOW(pin);
	interrupts();
	delayMicroseconds(480);
	noInterrupts();
	DIRECT_MODE_INPUT(pin);	// allow it to float
	delayMicroseconds(70);
	r = !DIRECT_READ(pin);
	interrupts();
	delayMicroseconds(410);
	return r;
}