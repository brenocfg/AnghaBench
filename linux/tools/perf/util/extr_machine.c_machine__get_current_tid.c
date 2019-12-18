#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct machine {int* current_tid; TYPE_1__* env; } ;
typedef  int pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  nr_cpus_online; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_NR_CPUS ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

pid_t machine__get_current_tid(struct machine *machine, int cpu)
{
	int nr_cpus = min(machine->env->nr_cpus_online, MAX_NR_CPUS);

	if (cpu < 0 || cpu >= nr_cpus || !machine->current_tid)
		return -1;

	return machine->current_tid[cpu];
}