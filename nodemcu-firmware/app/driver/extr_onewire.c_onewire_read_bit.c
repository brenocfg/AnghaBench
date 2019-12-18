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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECT_MODE_INPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIRECT_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIRECT_WRITE_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayMicroseconds (int) ; 
 int /*<<< orphan*/  interrupts () ; 
 int /*<<< orphan*/  noInterrupts () ; 

__attribute__((used)) static uint8_t onewire_read_bit(uint8_t pin)
{
	uint8_t r;

	noInterrupts();
	DIRECT_WRITE_LOW(pin);

	delayMicroseconds(5);
	DIRECT_MODE_INPUT(pin);	// let pin float, pull up will raise
	delayMicroseconds(8);
	r = DIRECT_READ(pin);
	interrupts();
	delayMicroseconds(52);
	return r;
}