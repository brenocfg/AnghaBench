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

/* Variables and functions */
 int EINVAL ; 
 int WDT_MAX_TIME ; 
 int wdt_time ; 

__attribute__((used)) static int ks8695_wdt_settimeout(int new_time)
{
	/*
	 * All counting occurs at KS8695_CLOCK_RATE / 128 = 0.256 Hz
	 *
	 * Since WDV is a 16-bit counter, the maximum period is
	 * 65536 / 0.256 = 256 seconds.
	 */
	if ((new_time <= 0) || (new_time > WDT_MAX_TIME))
		return -EINVAL;

	/* Set new watchdog time. It will be used when
	   ks8695_wdt_start() is called. */
	wdt_time = new_time;
	return 0;
}