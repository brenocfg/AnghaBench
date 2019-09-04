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
 scalar_t__ machine_is_netwinder () ; 
 int timeout ; 
 int timeoutM ; 

__attribute__((used)) static int wdt977_set_timeout(int t)
{
	int tmrval;

	/* convert seconds to minutes, rounding up */
	tmrval = (t + 59) / 60;

	if (machine_is_netwinder()) {
		/* we have a hw bug somewhere, so each 977 minute is actually
		 * only 30sec. This limits the max timeout to half of device
		 * max of 255 minutes...
		 */
		tmrval += tmrval;
	}

	if (tmrval < 1 || tmrval > 255)
		return -EINVAL;

	/* timeout is the timeout in seconds, timeoutM is
	   the timeout in minutes) */
	timeout = t;
	timeoutM = tmrval;
	return 0;
}