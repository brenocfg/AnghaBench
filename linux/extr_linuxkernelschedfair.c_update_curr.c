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
typedef  scalar_t__ u64 ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  exec_max; } ;
struct sched_entity {int /*<<< orphan*/  vruntime; int /*<<< orphan*/  sum_exec_runtime; TYPE_1__ statistics; scalar_t__ exec_start; } ;
struct cfs_rq {int /*<<< orphan*/  exec_clock; struct sched_entity* curr; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  account_cfs_rq_runtime (struct cfs_rq*,scalar_t__) ; 
 int /*<<< orphan*/  account_group_exec_runtime (struct task_struct*,scalar_t__) ; 
 scalar_t__ calc_delta_fair (scalar_t__,struct sched_entity*) ; 
 int /*<<< orphan*/  cgroup_account_cputime (struct task_struct*,scalar_t__) ; 
 scalar_t__ entity_is_task (struct sched_entity*) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_clock_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_of (struct cfs_rq*) ; 
 int /*<<< orphan*/  schedstat_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  schedstat_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct task_struct* task_of (struct sched_entity*) ; 
 int /*<<< orphan*/  trace_sched_stat_runtime (struct task_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_min_vruntime (struct cfs_rq*) ; 

__attribute__((used)) static void update_curr(struct cfs_rq *cfs_rq)
{
	struct sched_entity *curr = cfs_rq->curr;
	u64 now = rq_clock_task(rq_of(cfs_rq));
	u64 delta_exec;

	if (unlikely(!curr))
		return;

	delta_exec = now - curr->exec_start;
	if (unlikely((s64)delta_exec <= 0))
		return;

	curr->exec_start = now;

	schedstat_set(curr->statistics.exec_max,
		      max(delta_exec, curr->statistics.exec_max));

	curr->sum_exec_runtime += delta_exec;
	schedstat_add(cfs_rq->exec_clock, delta_exec);

	curr->vruntime += calc_delta_fair(delta_exec, curr);
	update_min_vruntime(cfs_rq);

	if (entity_is_task(curr)) {
		struct task_struct *curtask = task_of(curr);

		trace_sched_stat_runtime(curtask, delta_exec, curr->vruntime);
		cgroup_account_cputime(curtask, delta_exec);
		account_group_exec_runtime(curtask, delta_exec);
	}

	account_cfs_rq_runtime(cfs_rq, delta_exec);
}