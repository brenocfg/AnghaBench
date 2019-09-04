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
 int /*<<< orphan*/  DIRECT_MODE_INPUT (int) ; 
 int /*<<< orphan*/  DIRECT_WRITE_HIGH (int) ; 
 int /*<<< orphan*/  DIRECT_WRITE_LOW (int) ; 
 int /*<<< orphan*/  delayMicroseconds (int) ; 
 int /*<<< orphan*/  interrupts () ; 
 int /*<<< orphan*/  noInterrupts () ; 

__attribute__((used)) static void onewire_write_bit(uint8_t pin, uint8_t v, uint8_t power)
{
	if (v & 1) {
		noInterrupts();
		DIRECT_WRITE_LOW(pin);
		delayMicroseconds(5);
		if (power) {
			DIRECT_WRITE_HIGH(pin);
		} else {
			DIRECT_MODE_INPUT(pin);	// drive output high by the pull-up
		}
		delayMicroseconds(8);
		interrupts();
		delayMicroseconds(52);
	} else {
		noInterrupts();
		DIRECT_WRITE_LOW(pin);
		delayMicroseconds(65);
		if (power) {
			DIRECT_WRITE_HIGH(pin);
		} else {
			DIRECT_MODE_INPUT(pin);	// drive output high by the pull-up
		}
		interrupts();
		delayMicroseconds(5);
	}
}