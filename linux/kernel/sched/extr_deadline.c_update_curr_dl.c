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
typedef  scalar_t__ u64 ;
struct sched_dl_entity {int dl_yielded; int flags; int dl_throttled; int dl_overrun; scalar_t__ dl_boosted; int /*<<< orphan*/  runtime; } ;
struct TYPE_3__ {int /*<<< orphan*/  exec_max; } ;
struct TYPE_4__ {scalar_t__ exec_start; int /*<<< orphan*/  sum_exec_runtime; TYPE_1__ statistics; } ;
struct task_struct {struct sched_dl_entity dl; TYPE_2__ se; } ;
struct rt_rq {int /*<<< orphan*/  rt_runtime_lock; int /*<<< orphan*/  rt_time; } ;
struct rq {struct rt_rq rt; int /*<<< orphan*/  dl; struct task_struct* curr; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ENQUEUE_REPLENISH ; 
 int SCHED_FLAG_DL_OVERRUN ; 
 int SCHED_FLAG_RECLAIM ; 
 int /*<<< orphan*/  __dequeue_task_dl (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  account_group_exec_runtime (struct task_struct*,scalar_t__) ; 
 unsigned long arch_scale_cpu_capacity (int) ; 
 unsigned long arch_scale_freq_capacity (int) ; 
 scalar_t__ cap_scale (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  cgroup_account_cputime (struct task_struct*,scalar_t__) ; 
 int cpu_of (struct rq*) ; 
 scalar_t__ dl_entity_is_special (struct sched_dl_entity*) ; 
 scalar_t__ dl_runtime_exceeded (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  dl_task (struct task_struct*) ; 
 int /*<<< orphan*/  enqueue_task_dl (struct rq*,struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ grub_reclaim (scalar_t__,struct rq*,struct sched_dl_entity*) ; 
 int /*<<< orphan*/  is_leftmost (struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  on_dl_rq (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resched_curr (struct rq*) ; 
 scalar_t__ rq_clock_task (struct rq*) ; 
 scalar_t__ rt_bandwidth_enabled () ; 
 scalar_t__ sched_rt_bandwidth_account (struct rt_rq*) ; 
 int /*<<< orphan*/  schedstat_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_dl_timer (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void update_curr_dl(struct rq *rq)
{
	struct task_struct *curr = rq->curr;
	struct sched_dl_entity *dl_se = &curr->dl;
	u64 delta_exec, scaled_delta_exec;
	int cpu = cpu_of(rq);
	u64 now;

	if (!dl_task(curr) || !on_dl_rq(dl_se))
		return;

	/*
	 * Consumed budget is computed considering the time as
	 * observed by schedulable tasks (excluding time spent
	 * in hardirq context, etc.). Deadlines are instead
	 * computed using hard walltime. This seems to be the more
	 * natural solution, but the full ramifications of this
	 * approach need further study.
	 */
	now = rq_clock_task(rq);
	delta_exec = now - curr->se.exec_start;
	if (unlikely((s64)delta_exec <= 0)) {
		if (unlikely(dl_se->dl_yielded))
			goto throttle;
		return;
	}

	schedstat_set(curr->se.statistics.exec_max,
		      max(curr->se.statistics.exec_max, delta_exec));

	curr->se.sum_exec_runtime += delta_exec;
	account_group_exec_runtime(curr, delta_exec);

	curr->se.exec_start = now;
	cgroup_account_cputime(curr, delta_exec);

	if (dl_entity_is_special(dl_se))
		return;

	/*
	 * For tasks that participate in GRUB, we implement GRUB-PA: the
	 * spare reclaimed bandwidth is used to clock down frequency.
	 *
	 * For the others, we still need to scale reservation parameters
	 * according to current frequency and CPU maximum capacity.
	 */
	if (unlikely(dl_se->flags & SCHED_FLAG_RECLAIM)) {
		scaled_delta_exec = grub_reclaim(delta_exec,
						 rq,
						 &curr->dl);
	} else {
		unsigned long scale_freq = arch_scale_freq_capacity(cpu);
		unsigned long scale_cpu = arch_scale_cpu_capacity(cpu);

		scaled_delta_exec = cap_scale(delta_exec, scale_freq);
		scaled_delta_exec = cap_scale(scaled_delta_exec, scale_cpu);
	}

	dl_se->runtime -= scaled_delta_exec;

throttle:
	if (dl_runtime_exceeded(dl_se) || dl_se->dl_yielded) {
		dl_se->dl_throttled = 1;

		/* If requested, inform the user about runtime overruns. */
		if (dl_runtime_exceeded(dl_se) &&
		    (dl_se->flags & SCHED_FLAG_DL_OVERRUN))
			dl_se->dl_overrun = 1;

		__dequeue_task_dl(rq, curr, 0);
		if (unlikely(dl_se->dl_boosted || !start_dl_timer(curr)))
			enqueue_task_dl(rq, curr, ENQUEUE_REPLENISH);

		if (!is_leftmost(curr, &rq->dl))
			resched_curr(rq);
	}

	/*
	 * Because -- for now -- we share the rt bandwidth, we need to
	 * account our runtime there too, otherwise actual rt tasks
	 * would be able to exceed the shared quota.
	 *
	 * Account to the root rt group for now.
	 *
	 * The solution we're working towards is having the RT groups scheduled
	 * using deadline servers -- however there's a few nasties to figure
	 * out before that can happen.
	 */
	if (rt_bandwidth_enabled()) {
		struct rt_rq *rt_rq = &rq->rt;

		raw_spin_lock(&rt_rq->rt_runtime_lock);
		/*
		 * We'll let actual RT tasks worry about the overflow here, we
		 * have our own CBS to keep us inline; only account when RT
		 * bandwidth is relevant.
		 */
		if (sched_rt_bandwidth_account(rt_rq))
			rt_rq->rt_time += delta_exec;
		raw_spin_unlock(&rt_rq->rt_runtime_lock);
	}
}