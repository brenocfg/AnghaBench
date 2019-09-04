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
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

__attribute__((used)) static void _regulator_enable_delay(unsigned int delay)
{
	unsigned int ms = delay / 1000;
	unsigned int us = delay % 1000;

	if (ms > 0) {
		/*
		 * For small enough values, handle super-millisecond
		 * delays in the usleep_range() call below.
		 */
		if (ms < 20)
			us += ms * 1000;
		else
			msleep(ms);
	}

	/*
	 * Give the scheduler some room to coalesce with any other
	 * wakeup sources. For delays shorter than 10 us, don't even
	 * bother setting up high-resolution timers and just busy-
	 * loop.
	 */
	if (us >= 10)
		usleep_range(us, us + 100);
	else
		udelay(us);
}