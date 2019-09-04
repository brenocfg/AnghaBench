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
 int /*<<< orphan*/  KMSG_DUMP_HALT ; 
 int /*<<< orphan*/  SYSTEM_HALT ; 
 int /*<<< orphan*/  kernel_shutdown_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmsg_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_halt () ; 
 int /*<<< orphan*/  migrate_to_reboot_cpu () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  syscore_shutdown () ; 

void kernel_halt(void)
{
	kernel_shutdown_prepare(SYSTEM_HALT);
	migrate_to_reboot_cpu();
	syscore_shutdown();
	pr_emerg("System halted\n");
	kmsg_dump(KMSG_DUMP_HALT);
	machine_halt();
}