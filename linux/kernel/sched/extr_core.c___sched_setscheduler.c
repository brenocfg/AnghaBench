#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int sched_reset_on_fork; int policy; scalar_t__ rt_priority; int prio; struct sched_class* sched_class; int /*<<< orphan*/  cpus_ptr; scalar_t__ mm; } ;
struct sched_class {int dummy; } ;
struct sched_attr {int sched_policy; int sched_priority; int sched_flags; scalar_t__ sched_nice; } ;
struct rq_flags {int dummy; } ;
struct rq {TYPE_3__* rd; struct task_struct* stop; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_6__ {scalar_t__ rt_runtime; } ;
struct TYPE_9__ {TYPE_1__ rt_bandwidth; } ;
struct TYPE_7__ {scalar_t__ bw; } ;
struct TYPE_8__ {TYPE_2__ dl_bw; int /*<<< orphan*/ * span; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int DEQUEUE_MOVE ; 
 int DEQUEUE_NOCLOCK ; 
 int DEQUEUE_SAVE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENQUEUE_HEAD ; 
 int EPERM ; 
 int MAX_DL_PRIO ; 
 int MAX_RT_PRIO ; 
 int MAX_USER_RT_PRIO ; 
 int /*<<< orphan*/  RLIMIT_RTPRIO ; 
 int SCHED_FLAG_ALL ; 
 int SCHED_FLAG_RESET_ON_FORK ; 
 int SCHED_FLAG_SUGOV ; 
 int SCHED_FLAG_UTIL_CLAMP ; 
 int /*<<< orphan*/  __checkparam_dl (struct sched_attr const*) ; 
 int /*<<< orphan*/  __setscheduler (struct rq*,struct task_struct*,struct sched_attr const*,int) ; 
 int /*<<< orphan*/  __setscheduler_uclamp (struct task_struct*,struct sched_attr const*) ; 
 int /*<<< orphan*/  balance_callback (struct rq*) ; 
 int /*<<< orphan*/  can_nice (struct task_struct*,scalar_t__) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_class_changed (struct rq*,struct task_struct*,struct sched_class const*,int) ; 
 int /*<<< orphan*/  check_same_owner (struct task_struct*) ; 
 int /*<<< orphan*/  cpumask_subset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_read_lock () ; 
 int /*<<< orphan*/  cpuset_read_unlock () ; 
 int /*<<< orphan*/  dequeue_task (struct rq*,struct task_struct*,int) ; 
 scalar_t__ dl_bandwidth_enabled () ; 
 scalar_t__ dl_param_changed (struct task_struct*,struct sched_attr const*) ; 
 scalar_t__ dl_policy (int) ; 
 scalar_t__ dl_task (struct task_struct*) ; 
 int /*<<< orphan*/  enqueue_task (struct rq*,struct task_struct*,int) ; 
 scalar_t__ fair_policy (int) ; 
 int /*<<< orphan*/  idle_policy (int) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  put_prev_task (struct rq*,struct task_struct*) ; 
 scalar_t__ rt_bandwidth_enabled () ; 
 int rt_effective_prio (struct task_struct*,int) ; 
 int /*<<< orphan*/  rt_mutex_adjust_pi (struct task_struct*) ; 
 int rt_policy (int) ; 
 scalar_t__ sched_dl_overflow (struct task_struct*,int,struct sched_attr const*) ; 
 int security_task_setscheduler (struct task_struct*) ; 
 int /*<<< orphan*/  set_next_task (struct rq*,struct task_struct*) ; 
 int task_current (struct rq*,struct task_struct*) ; 
 TYPE_4__* task_group (struct task_struct*) ; 
 int /*<<< orphan*/  task_group_is_autogroup (TYPE_4__*) ; 
 scalar_t__ task_has_idle_policy (struct task_struct*) ; 
 scalar_t__ task_nice (struct task_struct*) ; 
 int task_on_rq_queued (struct task_struct*) ; 
 unsigned long task_rlimit (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct rq* task_rq_lock (struct task_struct*,struct rq_flags*) ; 
 int /*<<< orphan*/  task_rq_unlock (struct rq*,struct task_struct*,struct rq_flags*) ; 
 int uclamp_validate (struct task_struct*,struct sched_attr const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_rq_clock (struct rq*) ; 
 int /*<<< orphan*/  valid_policy (int) ; 

__attribute__((used)) static int __sched_setscheduler(struct task_struct *p,
				const struct sched_attr *attr,
				bool user, bool pi)
{
	int newprio = dl_policy(attr->sched_policy) ? MAX_DL_PRIO - 1 :
		      MAX_RT_PRIO - 1 - attr->sched_priority;
	int retval, oldprio, oldpolicy = -1, queued, running;
	int new_effective_prio, policy = attr->sched_policy;
	const struct sched_class *prev_class;
	struct rq_flags rf;
	int reset_on_fork;
	int queue_flags = DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCLOCK;
	struct rq *rq;

	/* The pi code expects interrupts enabled */
	BUG_ON(pi && in_interrupt());
recheck:
	/* Double check policy once rq lock held: */
	if (policy < 0) {
		reset_on_fork = p->sched_reset_on_fork;
		policy = oldpolicy = p->policy;
	} else {
		reset_on_fork = !!(attr->sched_flags & SCHED_FLAG_RESET_ON_FORK);

		if (!valid_policy(policy))
			return -EINVAL;
	}

	if (attr->sched_flags & ~(SCHED_FLAG_ALL | SCHED_FLAG_SUGOV))
		return -EINVAL;

	/*
	 * Valid priorities for SCHED_FIFO and SCHED_RR are
	 * 1..MAX_USER_RT_PRIO-1, valid priority for SCHED_NORMAL,
	 * SCHED_BATCH and SCHED_IDLE is 0.
	 */
	if ((p->mm && attr->sched_priority > MAX_USER_RT_PRIO-1) ||
	    (!p->mm && attr->sched_priority > MAX_RT_PRIO-1))
		return -EINVAL;
	if ((dl_policy(policy) && !__checkparam_dl(attr)) ||
	    (rt_policy(policy) != (attr->sched_priority != 0)))
		return -EINVAL;

	/*
	 * Allow unprivileged RT tasks to decrease priority:
	 */
	if (user && !capable(CAP_SYS_NICE)) {
		if (fair_policy(policy)) {
			if (attr->sched_nice < task_nice(p) &&
			    !can_nice(p, attr->sched_nice))
				return -EPERM;
		}

		if (rt_policy(policy)) {
			unsigned long rlim_rtprio =
					task_rlimit(p, RLIMIT_RTPRIO);

			/* Can't set/change the rt policy: */
			if (policy != p->policy && !rlim_rtprio)
				return -EPERM;

			/* Can't increase priority: */
			if (attr->sched_priority > p->rt_priority &&
			    attr->sched_priority > rlim_rtprio)
				return -EPERM;
		}

		 /*
		  * Can't set/change SCHED_DEADLINE policy at all for now
		  * (safest behavior); in the future we would like to allow
		  * unprivileged DL tasks to increase their relative deadline
		  * or reduce their runtime (both ways reducing utilization)
		  */
		if (dl_policy(policy))
			return -EPERM;

		/*
		 * Treat SCHED_IDLE as nice 20. Only allow a switch to
		 * SCHED_NORMAL if the RLIMIT_NICE would normally permit it.
		 */
		if (task_has_idle_policy(p) && !idle_policy(policy)) {
			if (!can_nice(p, task_nice(p)))
				return -EPERM;
		}

		/* Can't change other user's priorities: */
		if (!check_same_owner(p))
			return -EPERM;

		/* Normal users shall not reset the sched_reset_on_fork flag: */
		if (p->sched_reset_on_fork && !reset_on_fork)
			return -EPERM;
	}

	if (user) {
		if (attr->sched_flags & SCHED_FLAG_SUGOV)
			return -EINVAL;

		retval = security_task_setscheduler(p);
		if (retval)
			return retval;
	}

	/* Update task specific "requested" clamps */
	if (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP) {
		retval = uclamp_validate(p, attr);
		if (retval)
			return retval;
	}

	if (pi)
		cpuset_read_lock();

	/*
	 * Make sure no PI-waiters arrive (or leave) while we are
	 * changing the priority of the task:
	 *
	 * To be able to change p->policy safely, the appropriate
	 * runqueue lock must be held.
	 */
	rq = task_rq_lock(p, &rf);
	update_rq_clock(rq);

	/*
	 * Changing the policy of the stop threads its a very bad idea:
	 */
	if (p == rq->stop) {
		retval = -EINVAL;
		goto unlock;
	}

	/*
	 * If not changing anything there's no need to proceed further,
	 * but store a possible modification of reset_on_fork.
	 */
	if (unlikely(policy == p->policy)) {
		if (fair_policy(policy) && attr->sched_nice != task_nice(p))
			goto change;
		if (rt_policy(policy) && attr->sched_priority != p->rt_priority)
			goto change;
		if (dl_policy(policy) && dl_param_changed(p, attr))
			goto change;
		if (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP)
			goto change;

		p->sched_reset_on_fork = reset_on_fork;
		retval = 0;
		goto unlock;
	}
change:

	if (user) {
#ifdef CONFIG_RT_GROUP_SCHED
		/*
		 * Do not allow realtime tasks into groups that have no runtime
		 * assigned.
		 */
		if (rt_bandwidth_enabled() && rt_policy(policy) &&
				task_group(p)->rt_bandwidth.rt_runtime == 0 &&
				!task_group_is_autogroup(task_group(p))) {
			retval = -EPERM;
			goto unlock;
		}
#endif
#ifdef CONFIG_SMP
		if (dl_bandwidth_enabled() && dl_policy(policy) &&
				!(attr->sched_flags & SCHED_FLAG_SUGOV)) {
			cpumask_t *span = rq->rd->span;

			/*
			 * Don't allow tasks with an affinity mask smaller than
			 * the entire root_domain to become SCHED_DEADLINE. We
			 * will also fail if there's no bandwidth available.
			 */
			if (!cpumask_subset(span, p->cpus_ptr) ||
			    rq->rd->dl_bw.bw == 0) {
				retval = -EPERM;
				goto unlock;
			}
		}
#endif
	}

	/* Re-check policy now with rq lock held: */
	if (unlikely(oldpolicy != -1 && oldpolicy != p->policy)) {
		policy = oldpolicy = -1;
		task_rq_unlock(rq, p, &rf);
		if (pi)
			cpuset_read_unlock();
		goto recheck;
	}

	/*
	 * If setscheduling to SCHED_DEADLINE (or changing the parameters
	 * of a SCHED_DEADLINE task) we need to check if enough bandwidth
	 * is available.
	 */
	if ((dl_policy(policy) || dl_task(p)) && sched_dl_overflow(p, policy, attr)) {
		retval = -EBUSY;
		goto unlock;
	}

	p->sched_reset_on_fork = reset_on_fork;
	oldprio = p->prio;

	if (pi) {
		/*
		 * Take priority boosted tasks into account. If the new
		 * effective priority is unchanged, we just store the new
		 * normal parameters and do not touch the scheduler class and
		 * the runqueue. This will be done when the task deboost
		 * itself.
		 */
		new_effective_prio = rt_effective_prio(p, newprio);
		if (new_effective_prio == oldprio)
			queue_flags &= ~DEQUEUE_MOVE;
	}

	queued = task_on_rq_queued(p);
	running = task_current(rq, p);
	if (queued)
		dequeue_task(rq, p, queue_flags);
	if (running)
		put_prev_task(rq, p);

	prev_class = p->sched_class;

	__setscheduler(rq, p, attr, pi);
	__setscheduler_uclamp(p, attr);

	if (queued) {
		/*
		 * We enqueue to tail when the priority of a task is
		 * increased (user space view).
		 */
		if (oldprio < p->prio)
			queue_flags |= ENQUEUE_HEAD;

		enqueue_task(rq, p, queue_flags);
	}
	if (running)
		set_next_task(rq, p);

	check_class_changed(rq, p, prev_class, oldprio);

	/* Avoid rq from going away on us: */
	preempt_disable();
	task_rq_unlock(rq, p, &rf);

	if (pi) {
		cpuset_read_unlock();
		rt_mutex_adjust_pi(p);
	}

	/* Run balance callbacks after we've adjusted the PI chain: */
	balance_callback(rq);
	preempt_enable();

	return 0;

unlock:
	task_rq_unlock(rq, p, &rf);
	if (pi)
		cpuset_read_unlock();
	return retval;
}