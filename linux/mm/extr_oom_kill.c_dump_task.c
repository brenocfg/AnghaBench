#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int /*<<< orphan*/  comm; TYPE_1__* signal; TYPE_2__* mm; int /*<<< orphan*/  tgid; int /*<<< orphan*/  pid; } ;
struct oom_control {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  total_vm; } ;
struct TYPE_5__ {int /*<<< orphan*/  oom_score_adj; } ;

/* Variables and functions */
 int /*<<< orphan*/  MM_SWAPENTS ; 
 struct task_struct* find_lock_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mm_counter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mm_rss (TYPE_2__*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  is_memcg_oom (struct oom_control*) ; 
 int /*<<< orphan*/  mm_pgtables_bytes (TYPE_2__*) ; 
 int /*<<< orphan*/  oom_cpuset_eligible (struct task_struct*,struct oom_control*) ; 
 scalar_t__ oom_unkillable_task (struct task_struct*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int dump_task(struct task_struct *p, void *arg)
{
	struct oom_control *oc = arg;
	struct task_struct *task;

	if (oom_unkillable_task(p))
		return 0;

	/* p may not have freeable memory in nodemask */
	if (!is_memcg_oom(oc) && !oom_cpuset_eligible(p, oc))
		return 0;

	task = find_lock_task_mm(p);
	if (!task) {
		/*
		 * This is a kthread or all of p's threads have already
		 * detached their mm's.  There's no need to report
		 * them; they can't be oom killed anyway.
		 */
		return 0;
	}

	pr_info("[%7d] %5d %5d %8lu %8lu %8ld %8lu         %5hd %s\n",
		task->pid, from_kuid(&init_user_ns, task_uid(task)),
		task->tgid, task->mm->total_vm, get_mm_rss(task->mm),
		mm_pgtables_bytes(task->mm),
		get_mm_counter(task->mm, MM_SWAPENTS),
		task->signal->oom_score_adj, task->comm);
	task_unlock(task);

	return 0;
}