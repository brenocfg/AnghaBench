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
 int /*<<< orphan*/  emergency_restart () ; 
 scalar_t__ force_boot ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static void watchdog_fire(void)
{
	if (force_boot) {
		pr_crit("Initiating system reboot\n");
		emergency_restart();
		pr_crit("Reboot didn't ?????\n");
	}

	else {
		pr_crit("Immediate Reboot Disabled\n");
		pr_crit("System will reset when watchdog timer times out!\n");
	}
}