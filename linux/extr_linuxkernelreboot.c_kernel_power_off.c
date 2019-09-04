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
 int /*<<< orphan*/  KMSG_DUMP_POWEROFF ; 
 int /*<<< orphan*/  SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  kernel_shutdown_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmsg_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_power_off () ; 
 int /*<<< orphan*/  migrate_to_reboot_cpu () ; 
 int /*<<< orphan*/  pm_power_off_prepare () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  syscore_shutdown () ; 

void kernel_power_off(void)
{
	kernel_shutdown_prepare(SYSTEM_POWER_OFF);
	if (pm_power_off_prepare)
		pm_power_off_prepare();
	migrate_to_reboot_cpu();
	syscore_shutdown();
	pr_emerg("Power down\n");
	kmsg_dump(KMSG_DUMP_POWEROFF);
	machine_power_off();
}