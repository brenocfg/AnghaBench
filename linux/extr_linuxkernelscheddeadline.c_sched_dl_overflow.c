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
struct TYPE_2__ {scalar_t__ dl_bw; int /*<<< orphan*/  inactive_timer; } ;
struct task_struct {TYPE_1__ dl; } ;
struct sched_attr {scalar_t__ sched_deadline; scalar_t__ sched_runtime; int sched_flags; scalar_t__ sched_period; } ;
struct dl_bw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int SCHED_FLAG_SUGOV ; 
 int /*<<< orphan*/  __dl_add (struct dl_bw*,scalar_t__,int) ; 
 int /*<<< orphan*/  __dl_overflow (struct dl_bw*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __dl_sub (struct dl_bw*,scalar_t__,int) ; 
 int dl_bw_cpus (int /*<<< orphan*/ ) ; 
 struct dl_bw* dl_bw_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_change_utilization (struct task_struct*,scalar_t__) ; 
 scalar_t__ dl_policy (int) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_cpu (struct task_struct*) ; 
 scalar_t__ task_has_dl_policy (struct task_struct*) ; 
 scalar_t__ to_ratio (scalar_t__,scalar_t__) ; 

int sched_dl_overflow(struct task_struct *p, int policy,
		      const struct sched_attr *attr)
{
	struct dl_bw *dl_b = dl_bw_of(task_cpu(p));
	u64 period = attr->sched_period ?: attr->sched_deadline;
	u64 runtime = attr->sched_runtime;
	u64 new_bw = dl_policy(policy) ? to_ratio(period, runtime) : 0;
	int cpus, err = -1;

	if (attr->sched_flags & SCHED_FLAG_SUGOV)
		return 0;

	/* !deadline task may carry old deadline bandwidth */
	if (new_bw == p->dl.dl_bw && task_has_dl_policy(p))
		return 0;

	/*
	 * Either if a task, enters, leave, or stays -deadline but changes
	 * its parameters, we may need to update accordingly the total
	 * allocated bandwidth of the container.
	 */
	raw_spin_lock(&dl_b->lock);
	cpus = dl_bw_cpus(task_cpu(p));
	if (dl_policy(policy) && !task_has_dl_policy(p) &&
	    !__dl_overflow(dl_b, cpus, 0, new_bw)) {
		if (hrtimer_active(&p->dl.inactive_timer))
			__dl_sub(dl_b, p->dl.dl_bw, cpus);
		__dl_add(dl_b, new_bw, cpus);
		err = 0;
	} else if (dl_policy(policy) && task_has_dl_policy(p) &&
		   !__dl_overflow(dl_b, cpus, p->dl.dl_bw, new_bw)) {
		/*
		 * XXX this is slightly incorrect: when the task
		 * utilization decreases, we should delay the total
		 * utilization change until the task's 0-lag point.
		 * But this would require to set the task's "inactive
		 * timer" when the task is not inactive.
		 */
		__dl_sub(dl_b, p->dl.dl_bw, cpus);
		__dl_add(dl_b, new_bw, cpus);
		dl_change_utilization(p, new_bw);
		err = 0;
	} else if (!dl_policy(policy) && task_has_dl_policy(p)) {
		/*
		 * Do not decrease the total deadline utilization here,
		 * switched_from_dl() will take care to do it at the correct
		 * (0-lag) time.
		 */
		err = 0;
	}
	raw_spin_unlock(&dl_b->lock);

	return err;
}