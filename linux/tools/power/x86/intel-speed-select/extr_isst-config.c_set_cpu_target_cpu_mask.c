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
 int /*<<< orphan*/  CPU_ISSET_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_SET_S (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t alloc_cpu_set (int /*<<< orphan*/ *) ; 
 int max_target_cpus ; 
 int /*<<< orphan*/  present_cpumask ; 
 int /*<<< orphan*/  present_cpumask_size ; 
 int /*<<< orphan*/  target_cpumask ; 
 size_t target_cpumask_size ; 
 int /*<<< orphan*/ * target_cpus ; 

__attribute__((used)) static void set_cpu_target_cpu_mask(void)
{
	size_t size;
	int i;

	size = alloc_cpu_set(&target_cpumask);
	target_cpumask_size = size;
	for (i = 0; i < max_target_cpus; ++i) {
		if (!CPU_ISSET_S(target_cpus[i], present_cpumask_size,
				 present_cpumask))
			continue;

		CPU_SET_S(target_cpus[i], size, target_cpumask);
	}
}