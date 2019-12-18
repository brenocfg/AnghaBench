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
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET_S (int,size_t,int /*<<< orphan*/ *) ; 
 int max_cpu_num ; 

void for_all_cpus_in_set(size_t set_size, cpu_set_t *cpu_set, int (func)(int))
{
	int cpu_num;

	for (cpu_num = 0; cpu_num <= max_cpu_num; ++cpu_num)
		if (CPU_ISSET_S(cpu_num, set_size, cpu_set))
			func(cpu_num);
}