#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct oom_control {int /*<<< orphan*/  nodemask; int /*<<< orphan*/  memcg; scalar_t__ order; int /*<<< orphan*/  gfp_mask; } ;
struct TYPE_4__ {TYPE_1__* signal; int /*<<< orphan*/  comm; } ;
struct TYPE_3__ {int /*<<< orphan*/  oom_score_adj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_COMPACTION ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHOW_MEM_FILTER_NODES ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  dump_oom_summary (struct oom_control*,struct task_struct*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  dump_tasks (struct oom_control*) ; 
 int /*<<< orphan*/  dump_unreclaimable_slab () ; 
 scalar_t__ is_dump_unreclaim_slabs () ; 
 scalar_t__ is_memcg_oom (struct oom_control*) ; 
 int /*<<< orphan*/  mem_cgroup_print_oom_meminfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  show_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_oom_dump_tasks ; 

__attribute__((used)) static void dump_header(struct oom_control *oc, struct task_struct *p)
{
	pr_warn("%s invoked oom-killer: gfp_mask=%#x(%pGg), order=%d, oom_score_adj=%hd\n",
		current->comm, oc->gfp_mask, &oc->gfp_mask, oc->order,
			current->signal->oom_score_adj);
	if (!IS_ENABLED(CONFIG_COMPACTION) && oc->order)
		pr_warn("COMPACTION is disabled!!!\n");

	dump_stack();
	if (is_memcg_oom(oc))
		mem_cgroup_print_oom_meminfo(oc->memcg);
	else {
		show_mem(SHOW_MEM_FILTER_NODES, oc->nodemask);
		if (is_dump_unreclaim_slabs())
			dump_unreclaimable_slab();
	}
	if (sysctl_oom_dump_tasks)
		dump_tasks(oc);
	if (p)
		dump_oom_summary(oc, p);
}