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
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  cpu_stop_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int stop_machine_cpuslocked (int /*<<< orphan*/ ,void*,struct cpumask const*) ; 

int stop_machine(cpu_stop_fn_t fn, void *data, const struct cpumask *cpus)
{
	int ret;

	/* No CPUs can come up or down during this. */
	cpus_read_lock();
	ret = stop_machine_cpuslocked(fn, data, cpus);
	cpus_read_unlock();
	return ret;
}