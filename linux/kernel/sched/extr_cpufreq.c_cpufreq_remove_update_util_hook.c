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
 int /*<<< orphan*/  cpufreq_update_util_data ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cpufreq_remove_update_util_hook(int cpu)
{
	rcu_assign_pointer(per_cpu(cpufreq_update_util_data, cpu), NULL);
}