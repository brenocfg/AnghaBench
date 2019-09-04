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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ PULSEIN_LOOPS_PER_USEC ; 
 scalar_t__ micros () ; 

uint32_t pulseIn_low(volatile uint8_t *reg, uint32_t timeout)
{
	uint32_t timeout_count = timeout * PULSEIN_LOOPS_PER_USEC;
	uint32_t usec_start, usec_stop;
	
	// wait for any previous pulse to end
	while (!*reg) {
		if (--timeout_count == 0) return 0;
	}
	// wait for the pulse to start
	while (*reg) {
		if (--timeout_count == 0) return 0;
	}
	usec_start = micros();
	// wait for the pulse to stop
	while (!*reg) {
		if (--timeout_count == 0) return 0;
	}
	usec_stop = micros();
	return usec_stop - usec_start;
}