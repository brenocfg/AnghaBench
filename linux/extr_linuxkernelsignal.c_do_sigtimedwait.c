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
struct timespec {int dummy; } ;
struct task_struct {TYPE_1__* sighand; int /*<<< orphan*/  real_blocked; int /*<<< orphan*/  timer_slack_ns; int /*<<< orphan*/  blocked; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  scalar_t__ ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 scalar_t__ KTIME_MAX ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_task_blocked (struct task_struct*,int /*<<< orphan*/ *) ; 
 struct task_struct* current ; 
 int dequeue_signal (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int freezable_schedule_hrtimeout_range (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  sigandsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdelsetmask (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signotset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ timespec_to_ktime (struct timespec const) ; 
 int /*<<< orphan*/  timespec_valid (struct timespec const*) ; 

__attribute__((used)) static int do_sigtimedwait(const sigset_t *which, siginfo_t *info,
		    const struct timespec *ts)
{
	ktime_t *to = NULL, timeout = KTIME_MAX;
	struct task_struct *tsk = current;
	sigset_t mask = *which;
	int sig, ret = 0;

	if (ts) {
		if (!timespec_valid(ts))
			return -EINVAL;
		timeout = timespec_to_ktime(*ts);
		to = &timeout;
	}

	/*
	 * Invert the set of allowed signals to get those we want to block.
	 */
	sigdelsetmask(&mask, sigmask(SIGKILL) | sigmask(SIGSTOP));
	signotset(&mask);

	spin_lock_irq(&tsk->sighand->siglock);
	sig = dequeue_signal(tsk, &mask, info);
	if (!sig && timeout) {
		/*
		 * None ready, temporarily unblock those we're interested
		 * while we are sleeping in so that we'll be awakened when
		 * they arrive. Unblocking is always fine, we can avoid
		 * set_current_blocked().
		 */
		tsk->real_blocked = tsk->blocked;
		sigandsets(&tsk->blocked, &tsk->blocked, &mask);
		recalc_sigpending();
		spin_unlock_irq(&tsk->sighand->siglock);

		__set_current_state(TASK_INTERRUPTIBLE);
		ret = freezable_schedule_hrtimeout_range(to, tsk->timer_slack_ns,
							 HRTIMER_MODE_REL);
		spin_lock_irq(&tsk->sighand->siglock);
		__set_task_blocked(tsk, &tsk->real_blocked);
		sigemptyset(&tsk->real_blocked);
		sig = dequeue_signal(tsk, &mask, info);
	}
	spin_unlock_irq(&tsk->sighand->siglock);

	if (sig)
		return sig;
	return ret ? -EINTR : -EAGAIN;
}