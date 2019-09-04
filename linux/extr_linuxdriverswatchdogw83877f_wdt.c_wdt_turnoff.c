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
 int /*<<< orphan*/  WDT_DISABLE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wdt_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_turnoff(void)
{
	/* Stop the timer */
	del_timer(&timer);

	wdt_change(WDT_DISABLE);

	pr_info("Watchdog timer is now disabled...\n");
}