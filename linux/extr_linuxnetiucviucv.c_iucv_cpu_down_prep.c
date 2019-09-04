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
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpumask_clear_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_allow_cpu ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int /*<<< orphan*/  iucv_irq_cpumask ; 
 int /*<<< orphan*/  iucv_path_table ; 
 int /*<<< orphan*/  iucv_retrieve_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int iucv_cpu_down_prep(unsigned int cpu)
{
	cpumask_t cpumask;

	if (!iucv_path_table)
		return 0;

	cpumask_copy(&cpumask, &iucv_buffer_cpumask);
	cpumask_clear_cpu(cpu, &cpumask);
	if (cpumask_empty(&cpumask))
		/* Can't offline last IUCV enabled cpu. */
		return -EINVAL;

	iucv_retrieve_cpu(NULL);
	if (!cpumask_empty(&iucv_irq_cpumask))
		return 0;
	smp_call_function_single(cpumask_first(&iucv_buffer_cpumask),
				 iucv_allow_cpu, NULL, 1);
	return 0;
}