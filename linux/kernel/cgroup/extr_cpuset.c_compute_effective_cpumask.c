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
struct cpuset {struct cpumask* effective_cpus; struct cpumask* cpus_allowed; int /*<<< orphan*/  subparts_cpus; scalar_t__ nr_subparts_cpus; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 struct cpumask* cpu_active_mask ; 
 int /*<<< orphan*/  cpumask_and (struct cpumask*,struct cpumask*,struct cpumask*) ; 
 int /*<<< orphan*/  cpumask_or (struct cpumask*,struct cpumask*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compute_effective_cpumask(struct cpumask *new_cpus,
				      struct cpuset *cs, struct cpuset *parent)
{
	if (parent->nr_subparts_cpus) {
		cpumask_or(new_cpus, parent->effective_cpus,
			   parent->subparts_cpus);
		cpumask_and(new_cpus, new_cpus, cs->cpus_allowed);
		cpumask_and(new_cpus, new_cpus, cpu_active_mask);
	} else {
		cpumask_and(new_cpus, cs->cpus_allowed, parent->effective_cpus);
	}
}