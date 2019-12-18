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
typedef  unsigned long long u64 ;
struct TYPE_3__ {unsigned long long sum_exec_runtime; } ;
struct task_struct {TYPE_1__ se; TYPE_2__* sched_class; int /*<<< orphan*/  on_cpu; } ;
struct rq_flags {int dummy; } ;
struct rq {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* update_curr ) (struct rq*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  prefetch_curr_exec_start (struct task_struct*) ; 
 int /*<<< orphan*/  stub1 (struct rq*) ; 
 scalar_t__ task_current (struct rq*,struct task_struct*) ; 
 scalar_t__ task_on_rq_queued (struct task_struct*) ; 
 struct rq* task_rq_lock (struct task_struct*,struct rq_flags*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,struct task_struct*,struct rq_flags*) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 

unsigned long long task_sched_runtime(struct task_struct *p)
{
	struct rq_flags rf;
	struct rq *rq;
	u64 ns;

#if defined(CONFIG_64BIT) && defined(CONFIG_SMP)
	/*
	 * 64-bit doesn't need locks to atomically read a 64-bit value.
	 * So we have a optimization chance when the task's delta_exec is 0.
	 * Reading ->on_cpu is racy, but this is ok.
	 *
	 * If we race with it leaving CPU, we'll take a lock. So we're correct.
	 * If we race with it entering CPU, unaccounted time is 0. This is
	 * indistinguishable from the read occurring a few cycles earlier.
	 * If we see ->on_cpu without ->on_rq, the task is leaving, and has
	 * been accounted, so we're correct here as well.
	 */
	if (!p->on_cpu || !task_on_rq_queued(p))
		return p->se.sum_exec_runtime;
#endif

	rq = task_rq_lock(p, &rf);
	/*
	 * Must be ->curr _and_ ->on_rq.  If dequeued, we would
	 * project cycles that may never be accounted to this
	 * thread, breaking clock_gettime().
	 */
	if (task_current(rq, p) && task_on_rq_queued(p)) {
		prefetch_curr_exec_start(p);
		update_rq_clock(rq);
		p->sched_class->update_curr(rq);
	}
	ns = p->se.sum_exec_runtime;
	task_rq_unlock(rq, p, &rf);

	return ns;
}