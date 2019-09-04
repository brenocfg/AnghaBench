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
struct task_struct {int dummy; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void sched_show_numa(struct task_struct *p, struct seq_file *m)
{
#ifdef CONFIG_NUMA_BALANCING
	struct mempolicy *pol;

	if (p->mm)
		P(mm->numa_scan_seq);

	task_lock(p);
	pol = p->mempolicy;
	if (pol && !(pol->flags & MPOL_F_MORON))
		pol = NULL;
	mpol_get(pol);
	task_unlock(p);

	P(numa_pages_migrated);
	P(numa_preferred_nid);
	P(total_numa_faults);
	SEQ_printf(m, "current_node=%d, numa_group_id=%d\n",
			task_node(p), task_numa_group_id(p));
	show_numa_stats(p, m);
	mpol_put(pol);
#endif
}