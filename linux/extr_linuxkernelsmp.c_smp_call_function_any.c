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
typedef  int /*<<< orphan*/  smp_call_func_t ;

/* Variables and functions */
 scalar_t__ cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 unsigned int cpumask_any_and (struct cpumask const*,int /*<<< orphan*/ ) ; 
 unsigned int cpumask_first_and (struct cpumask const*,struct cpumask const*) ; 
 unsigned int cpumask_next_and (unsigned int,struct cpumask const*,struct cpumask const*) ; 
 struct cpumask* cpumask_of_node (int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_test_cpu (unsigned int,struct cpumask const*) ; 
 unsigned int get_cpu () ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  put_cpu () ; 
 int smp_call_function_single (unsigned int,int /*<<< orphan*/ ,void*,int) ; 

int smp_call_function_any(const struct cpumask *mask,
			  smp_call_func_t func, void *info, int wait)
{
	unsigned int cpu;
	const struct cpumask *nodemask;
	int ret;

	/* Try for same CPU (cheapest) */
	cpu = get_cpu();
	if (cpumask_test_cpu(cpu, mask))
		goto call;

	/* Try for same node. */
	nodemask = cpumask_of_node(cpu_to_node(cpu));
	for (cpu = cpumask_first_and(nodemask, mask); cpu < nr_cpu_ids;
	     cpu = cpumask_next_and(cpu, nodemask, mask)) {
		if (cpu_online(cpu))
			goto call;
	}

	/* Any online will do: smp_call_function_single handles nr_cpu_ids. */
	cpu = cpumask_any_and(mask, cpu_online_mask);
call:
	ret = smp_call_function_single(cpu, func, info, wait);
	put_cpu();
	return ret;
}