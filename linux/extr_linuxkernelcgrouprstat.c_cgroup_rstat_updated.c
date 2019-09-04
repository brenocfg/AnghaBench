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
struct cgroup_rstat_cpu {struct cgroup* updated_children; struct cgroup* updated_next; } ;
struct cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  raw_spinlock_t ;

/* Variables and functions */
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 struct cgroup_rstat_cpu* cgroup_rstat_cpu (struct cgroup*,int) ; 
 int /*<<< orphan*/  cgroup_rstat_cpu_lock ; 
 int /*<<< orphan*/ * per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_mb () ; 

void cgroup_rstat_updated(struct cgroup *cgrp, int cpu)
{
	raw_spinlock_t *cpu_lock = per_cpu_ptr(&cgroup_rstat_cpu_lock, cpu);
	struct cgroup *parent;
	unsigned long flags;

	/* nothing to do for root */
	if (!cgroup_parent(cgrp))
		return;

	/*
	 * Paired with the one in cgroup_rstat_cpu_pop_upated().  Either we
	 * see NULL updated_next or they see our updated stat.
	 */
	smp_mb();

	/*
	 * Because @parent's updated_children is terminated with @parent
	 * instead of NULL, we can tell whether @cgrp is on the list by
	 * testing the next pointer for NULL.
	 */
	if (cgroup_rstat_cpu(cgrp, cpu)->updated_next)
		return;

	raw_spin_lock_irqsave(cpu_lock, flags);

	/* put @cgrp and all ancestors on the corresponding updated lists */
	for (parent = cgroup_parent(cgrp); parent;
	     cgrp = parent, parent = cgroup_parent(cgrp)) {
		struct cgroup_rstat_cpu *rstatc = cgroup_rstat_cpu(cgrp, cpu);
		struct cgroup_rstat_cpu *prstatc = cgroup_rstat_cpu(parent, cpu);

		/*
		 * Both additions and removals are bottom-up.  If a cgroup
		 * is already in the tree, all ancestors are.
		 */
		if (rstatc->updated_next)
			break;

		rstatc->updated_next = prstatc->updated_children;
		prstatc->updated_children = cgrp;
	}

	raw_spin_unlock_irqrestore(cpu_lock, flags);
}