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
 int timeout ; 
 int timeoutW ; 

__attribute__((used)) static int wdt_set_timeout(int t)
{
	unsigned int tmrval;

	/*
	 * Convert seconds to watchdog counter time units, rounding up.
	 * On PCM-5335 watchdog units are 30 seconds/step with 15 sec startup
	 * value. This information is supplied in the PCM-5335 manual and was
	 * checked by me on a real board. This is a bit strange because W83977f
	 * datasheet says counter unit is in minutes!
	 */
	if (t < 15)
		return -EINVAL;

	tmrval = ((t + 15) + 29) / 30;

	if (tmrval > 255)
		return -EINVAL;

	/*
	 * timeout is the timeout in seconds,
	 * timeoutW is the timeout in watchdog counter units.
	 */
	timeoutW = tmrval;
	timeout = (timeoutW * 30) - 15;
	return 0;
}