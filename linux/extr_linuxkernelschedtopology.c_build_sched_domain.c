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
struct sched_domain_topology_level {int dummy; } ;
struct sched_domain_attr {int dummy; } ;
struct sched_domain {struct sched_domain* parent; scalar_t__ level; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sched_domain_level_max ; 
 int /*<<< orphan*/  sched_domain_span (struct sched_domain*) ; 
 struct sched_domain* sd_init (struct sched_domain_topology_level*,struct cpumask const*,struct sched_domain*,int) ; 
 int /*<<< orphan*/  set_domain_attribute (struct sched_domain*,struct sched_domain_attr*) ; 

__attribute__((used)) static struct sched_domain *build_sched_domain(struct sched_domain_topology_level *tl,
		const struct cpumask *cpu_map, struct sched_domain_attr *attr,
		struct sched_domain *child, int cpu)
{
	struct sched_domain *sd = sd_init(tl, cpu_map, child, cpu);

	if (child) {
		sd->level = child->level + 1;
		sched_domain_level_max = max(sched_domain_level_max, sd->level);
		child->parent = sd;

		if (!cpumask_subset(sched_domain_span(child),
				    sched_domain_span(sd))) {
			pr_err("BUG: arch topology borken\n");
#ifdef CONFIG_SCHED_DEBUG
			pr_err("     the %s domain not a subset of the %s domain\n",
					child->name, sd->name);
#endif
			/* Fixup, ensure @sd has at least @child CPUs. */
			cpumask_or(sched_domain_span(sd),
				   sched_domain_span(sd),
				   sched_domain_span(child));
		}

	}
	set_domain_attribute(sd, attr);

	return sd;
}