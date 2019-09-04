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
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 scalar_t__ U300_WDOG_FR ; 
 unsigned int U300_WDOG_FR_FEED_RESTART_TIMER ; 
 scalar_t__ U300_WDOG_TR ; 
 scalar_t__ virtbase ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int coh901327_settimeout(struct watchdog_device *wdt_dev,
				unsigned int time)
{
	wdt_dev->timeout = time;
	/* Set new timeout value */
	writew(time * 100, virtbase + U300_WDOG_TR);
	/* Feed the dog */
	writew(U300_WDOG_FR_FEED_RESTART_TIMER,
	       virtbase + U300_WDOG_FR);
	return 0;
}