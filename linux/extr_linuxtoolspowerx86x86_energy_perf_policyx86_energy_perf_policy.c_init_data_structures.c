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
 int /*<<< orphan*/ * CPU_ALLOC (scalar_t__) ; 
 int /*<<< orphan*/  CPU_ALLOC_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  CPU_ZERO_S (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpu_present_set ; 
 int /*<<< orphan*/  cpu_setsize ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  for_all_proc_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_cpu_present ; 
 scalar_t__ max_cpu_num ; 
 int /*<<< orphan*/  set_max_cpu_pkg_num ; 

void init_data_structures(void)
{
	for_all_proc_cpus(set_max_cpu_pkg_num);

	cpu_setsize = CPU_ALLOC_SIZE((max_cpu_num + 1));

	cpu_present_set = CPU_ALLOC((max_cpu_num + 1));
	if (cpu_present_set == NULL)
		err(3, "CPU_ALLOC");
	CPU_ZERO_S(cpu_setsize, cpu_present_set);
	for_all_proc_cpus(mark_cpu_present);
}