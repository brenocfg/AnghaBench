#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_NO_SETAFFINITY ; 
 int /*<<< orphan*/  cpu_hotplug_disable () ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 TYPE_1__* current ; 
 int reboot_cpu ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (TYPE_1__*,int /*<<< orphan*/ ) ; 

void migrate_to_reboot_cpu(void)
{
	/* The boot cpu is always logical cpu 0 */
	int cpu = reboot_cpu;

	cpu_hotplug_disable();

	/* Make certain the cpu I'm about to reboot on is online */
	if (!cpu_online(cpu))
		cpu = cpumask_first(cpu_online_mask);

	/* Prevent races with other tasks migrating this task */
	current->flags |= PF_NO_SETAFFINITY;

	/* Make certain I only run on the appropriate processor */
	set_cpus_allowed_ptr(current, cpumask_of(cpu));
}