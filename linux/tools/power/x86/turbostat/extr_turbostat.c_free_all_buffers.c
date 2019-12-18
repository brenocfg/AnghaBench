#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * put_ids; } ;
struct TYPE_13__ {int max_cpu_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FREE (int /*<<< orphan*/ *) ; 
 TYPE_2__* core_even ; 
 TYPE_2__* core_odd ; 
 int /*<<< orphan*/ * cpu_affinity_set ; 
 scalar_t__ cpu_affinity_setsize ; 
 int /*<<< orphan*/ * cpu_present_set ; 
 scalar_t__ cpu_present_setsize ; 
 TYPE_2__* cpus ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  free_fd_percpu () ; 
 TYPE_2__* irq_column_2_cpu ; 
 TYPE_2__* irqs_per_cpu ; 
 int /*<<< orphan*/ * outp ; 
 TYPE_2__* output_buffer ; 
 TYPE_2__* package_even ; 
 TYPE_2__* package_odd ; 
 TYPE_2__* thread_even ; 
 TYPE_2__* thread_odd ; 
 TYPE_1__ topo ; 

void free_all_buffers(void)
{
	int i;

	CPU_FREE(cpu_present_set);
	cpu_present_set = NULL;
	cpu_present_setsize = 0;

	CPU_FREE(cpu_affinity_set);
	cpu_affinity_set = NULL;
	cpu_affinity_setsize = 0;

	free(thread_even);
	free(core_even);
	free(package_even);

	thread_even = NULL;
	core_even = NULL;
	package_even = NULL;

	free(thread_odd);
	free(core_odd);
	free(package_odd);

	thread_odd = NULL;
	core_odd = NULL;
	package_odd = NULL;

	free(output_buffer);
	output_buffer = NULL;
	outp = NULL;

	free_fd_percpu();

	free(irq_column_2_cpu);
	free(irqs_per_cpu);

	for (i = 0; i <= topo.max_cpu_num; ++i) {
		if (cpus[i].put_ids)
			CPU_FREE(cpus[i].put_ids);
	}
	free(cpus);
}