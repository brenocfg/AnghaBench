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
struct cpuset {int /*<<< orphan*/  effective_cpus; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (struct cpumask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpuset* parent_cs (struct cpuset*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void guarantee_online_cpus(struct cpuset *cs, struct cpumask *pmask)
{
	while (!cpumask_intersects(cs->effective_cpus, cpu_online_mask)) {
		cs = parent_cs(cs);
		if (unlikely(!cs)) {
			/*
			 * The top cpuset doesn't have any online cpu as a
			 * consequence of a race between cpuset_hotplug_work
			 * and cpu hotplug notifier.  But we know the top
			 * cpuset's effective_cpus is on its way to to be
			 * identical to cpu_online_mask.
			 */
			cpumask_copy(pmask, cpu_online_mask);
			return;
		}
	}
	cpumask_and(pmask, cs->effective_cpus, cpu_online_mask);
}