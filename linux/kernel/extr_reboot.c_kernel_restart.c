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
 int /*<<< orphan*/  KMSG_DUMP_RESTART ; 
 int /*<<< orphan*/  kernel_restart_prepare (char*) ; 
 int /*<<< orphan*/  kmsg_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_restart (char*) ; 
 int /*<<< orphan*/  migrate_to_reboot_cpu () ; 
 int /*<<< orphan*/  pr_emerg (char*,...) ; 
 int /*<<< orphan*/  syscore_shutdown () ; 

void kernel_restart(char *cmd)
{
	kernel_restart_prepare(cmd);
	migrate_to_reboot_cpu();
	syscore_shutdown();
	if (!cmd)
		pr_emerg("Restarting system\n");
	else
		pr_emerg("Restarting system with command '%s'\n", cmd);
	kmsg_dump(KMSG_DUMP_RESTART);
	machine_restart(cmd);
}