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
typedef  int uint32_t ;

/* Variables and functions */
 int RTC_TCR ; 

void rtc_compensate(int adjust)
{
	uint32_t comp, interval, tcr;

	// This simple approach tries to maximize the interval.
	// Perhaps minimizing TCR would be better, so the
	// compensation is distributed more evenly across
	// many seconds, rather than saving it all up and then
	// altering one second up to +/- 0.38%
	if (adjust >= 0) {
		comp = adjust;
		interval = 256;
		while (1) {
			tcr = comp * interval;
			if (tcr < 128*256) break;
			if (--interval == 1) break;
		}
		tcr = tcr >> 8;
	} else {
		comp = -adjust;
		interval = 256;
		while (1) {
			tcr = comp * interval;
			if (tcr < 129*256) break;
			if (--interval == 1) break;
		}
		tcr = tcr >> 8;
		tcr = 256 - tcr;
	}
	RTC_TCR = ((interval - 1) << 8) | tcr;
}