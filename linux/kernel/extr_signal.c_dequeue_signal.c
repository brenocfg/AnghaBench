#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_3__* sighand; TYPE_2__* signal; int /*<<< orphan*/  pending; } ;
struct hrtimer {TYPE_1__* base; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_12__ {scalar_t__ si_sys_private; } ;
typedef  TYPE_4__ kernel_siginfo_t ;
struct TYPE_13__ {int /*<<< orphan*/  jobctl; } ;
struct TYPE_11__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_10__ {scalar_t__ it_real_incr; struct hrtimer real_timer; int /*<<< orphan*/  shared_pending; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* get_time ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  JOBCTL_STOP_DEQUEUED ; 
 int SIGALRM ; 
 int __dequeue_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int*) ; 
 TYPE_7__* current ; 
 int /*<<< orphan*/  hrtimer_forward (struct hrtimer*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hrtimer_is_queued (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_restart (struct hrtimer*) ; 
 int /*<<< orphan*/  posixtimer_rearm (TYPE_4__*) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int sig_kernel_stop (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ unlikely (int) ; 

int dequeue_signal(struct task_struct *tsk, sigset_t *mask, kernel_siginfo_t *info)
{
	bool resched_timer = false;
	int signr;

	/* We only dequeue private signals from ourselves, we don't let
	 * signalfd steal them
	 */
	signr = __dequeue_signal(&tsk->pending, mask, info, &resched_timer);
	if (!signr) {
		signr = __dequeue_signal(&tsk->signal->shared_pending,
					 mask, info, &resched_timer);
#ifdef CONFIG_POSIX_TIMERS
		/*
		 * itimer signal ?
		 *
		 * itimers are process shared and we restart periodic
		 * itimers in the signal delivery path to prevent DoS
		 * attacks in the high resolution timer case. This is
		 * compliant with the old way of self-restarting
		 * itimers, as the SIGALRM is a legacy signal and only
		 * queued once. Changing the restart behaviour to
		 * restart the timer in the signal dequeue path is
		 * reducing the timer noise on heavy loaded !highres
		 * systems too.
		 */
		if (unlikely(signr == SIGALRM)) {
			struct hrtimer *tmr = &tsk->signal->real_timer;

			if (!hrtimer_is_queued(tmr) &&
			    tsk->signal->it_real_incr != 0) {
				hrtimer_forward(tmr, tmr->base->get_time(),
						tsk->signal->it_real_incr);
				hrtimer_restart(tmr);
			}
		}
#endif
	}

	recalc_sigpending();
	if (!signr)
		return 0;

	if (unlikely(sig_kernel_stop(signr))) {
		/*
		 * Set a marker that we have dequeued a stop signal.  Our
		 * caller might release the siglock and then the pending
		 * stop signal it is about to process is no longer in the
		 * pending bitmasks, but must still be cleared by a SIGCONT
		 * (and overruled by a SIGKILL).  So those cases clear this
		 * shared flag after we've set it.  Note that this flag may
		 * remain set after the signal we return is ignored or
		 * handled.  That doesn't matter because its only purpose
		 * is to alert stop-signal processing code when another
		 * processor has come along and cleared the flag.
		 */
		current->jobctl |= JOBCTL_STOP_DEQUEUED;
	}
#ifdef CONFIG_POSIX_TIMERS
	if (resched_timer) {
		/*
		 * Release the siglock to ensure proper locking order
		 * of timer locks outside of siglocks.  Note, we leave
		 * irqs disabled here, since the posix-timers code is
		 * about to disable them again anyway.
		 */
		spin_unlock(&tsk->sighand->siglock);
		posixtimer_rearm(info);
		spin_lock(&tsk->sighand->siglock);

		/* Don't expose the si_sys_private value to userspace */
		info->si_sys_private = 0;
	}
#endif
	return signr;
}