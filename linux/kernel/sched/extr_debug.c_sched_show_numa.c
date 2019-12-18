#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {struct mempolicy* mempolicy; scalar_t__ mm; } ;
struct seq_file {int dummy; } ;
struct mempolicy {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  numa_scan_seq; } ;

/* Variables and functions */
 int MPOL_F_MORON ; 
 int /*<<< orphan*/  P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mm ; 
 int /*<<< orphan*/  mpol_get (struct mempolicy*) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int /*<<< orphan*/  numa_pages_migrated ; 
 int /*<<< orphan*/  numa_preferred_nid ; 
 int /*<<< orphan*/  show_numa_stats (struct task_struct*,struct seq_file*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_node (struct task_struct*) ; 
 int /*<<< orphan*/  task_numa_group_id (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  total_numa_faults ; 

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