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
typedef  void* u64 ;
struct TYPE_3__ {int /*<<< orphan*/  exec_max; } ;
struct TYPE_4__ {void* exec_start; int /*<<< orphan*/  sum_exec_runtime; TYPE_1__ statistics; } ;
struct task_struct {TYPE_2__ se; } ;
struct rq {struct task_struct* curr; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  account_group_exec_runtime (struct task_struct*,void*) ; 
 int /*<<< orphan*/  cgroup_account_cputime (struct task_struct*,void*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,void*) ; 
 void* rq_clock_task (struct rq*) ; 
 int /*<<< orphan*/  schedstat_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void put_prev_task_stop(struct rq *rq, struct task_struct *prev)
{
	struct task_struct *curr = rq->curr;
	u64 delta_exec;

	delta_exec = rq_clock_task(rq) - curr->se.exec_start;
	if (unlikely((s64)delta_exec < 0))
		delta_exec = 0;

	schedstat_set(curr->se.statistics.exec_max,
			max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runtime += delta_exec;
	account_group_exec_runtime(curr, delta_exec);

	curr->se.exec_start = rq_clock_task(rq);
	cgroup_account_cputime(curr, delta_exec);
}