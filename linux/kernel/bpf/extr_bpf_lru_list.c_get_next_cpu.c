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
 int /*<<< orphan*/  cpu_possible_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 

__attribute__((used)) static int get_next_cpu(int cpu)
{
	cpu = cpumask_next(cpu, cpu_possible_mask);
	if (cpu >= nr_cpu_ids)
		cpu = cpumask_first(cpu_possible_mask);
	return cpu;
}