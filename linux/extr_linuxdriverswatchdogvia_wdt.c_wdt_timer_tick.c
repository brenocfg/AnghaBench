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
struct timer_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ WDT_HEARTBEAT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  next_heartbeat ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  watchdog_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_dev ; 
 int /*<<< orphan*/  wdt_reset () ; 

__attribute__((used)) static void wdt_timer_tick(struct timer_list *unused)
{
	if (time_before(jiffies, next_heartbeat) ||
	   (!watchdog_active(&wdt_dev))) {
		wdt_reset();
		mod_timer(&timer, jiffies + WDT_HEARTBEAT);
	} else
		pr_crit("I will reboot your machine !\n");
}