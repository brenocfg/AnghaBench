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
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) () ;int /*<<< orphan*/  (* start ) () ;int /*<<< orphan*/  hw_states_num; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int avail_monitors ; 
 int /*<<< orphan*/  bind_cpu (int) ; 
 int cpu_count ; 
 int /*<<< orphan*/  dprint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** monitors ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 scalar_t__ wake_cpus ; 

int do_interval_measure(int i)
{
	unsigned int num;
	int cpu;

	if (wake_cpus)
		for (cpu = 0; cpu < cpu_count; cpu++)
			bind_cpu(cpu);

	for (num = 0; num < avail_monitors; num++) {
		dprint("HW C-state residency monitor: %s - States: %d\n",
		       monitors[num]->name, monitors[num]->hw_states_num);
		monitors[num]->start();
	}

	sleep(i);

	if (wake_cpus)
		for (cpu = 0; cpu < cpu_count; cpu++)
			bind_cpu(cpu);

	for (num = 0; num < avail_monitors; num++)
		monitors[num]->stop();


	return 0;
}