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
typedef  enum hk_flags { ____Placeholder_hk_flags } hk_flags ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_any_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int housekeeping_flags ; 
 int /*<<< orphan*/  housekeeping_mask ; 
 int /*<<< orphan*/  housekeeping_overriden ; 
 int smp_processor_id () ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

int housekeeping_any_cpu(enum hk_flags flags)
{
	if (static_branch_unlikely(&housekeeping_overriden))
		if (housekeeping_flags & flags)
			return cpumask_any_and(housekeeping_mask, cpu_online_mask);
	return smp_processor_id();
}