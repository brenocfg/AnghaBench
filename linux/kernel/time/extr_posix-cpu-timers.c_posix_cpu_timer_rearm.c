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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int /*<<< orphan*/  exit_state; } ;
struct sighand_struct {int dummy; } ;
struct cpu_timer {struct task_struct* task; } ;
struct TYPE_2__ {struct cpu_timer cpu; } ;
struct k_itimer {int /*<<< orphan*/  it_clock; TYPE_1__ it; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPUCLOCK_WHICH (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  arm_timer (struct k_itimer*) ; 
 int /*<<< orphan*/  bump_cpu_timer (struct k_itimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_clock_sample (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  cpu_clock_sample_group (int /*<<< orphan*/ ,struct task_struct*,int) ; 
 int /*<<< orphan*/  cpu_timer_setexpires (struct cpu_timer*,int /*<<< orphan*/ ) ; 
 struct sighand_struct* lock_task_sighand (struct task_struct*,unsigned long*) ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static void posix_cpu_timer_rearm(struct k_itimer *timer)
{
	clockid_t clkid = CPUCLOCK_WHICH(timer->it_clock);
	struct cpu_timer *ctmr = &timer->it.cpu;
	struct task_struct *p = ctmr->task;
	struct sighand_struct *sighand;
	unsigned long flags;
	u64 now;

	if (WARN_ON_ONCE(!p))
		return;

	/*
	 * Fetch the current sample and update the timer's expiry time.
	 */
	if (CPUCLOCK_PERTHREAD(timer->it_clock)) {
		now = cpu_clock_sample(clkid, p);
		bump_cpu_timer(timer, now);
		if (unlikely(p->exit_state))
			return;

		/* Protect timer list r/w in arm_timer() */
		sighand = lock_task_sighand(p, &flags);
		if (!sighand)
			return;
	} else {
		/*
		 * Protect arm_timer() and timer sampling in case of call to
		 * thread_group_cputime().
		 */
		sighand = lock_task_sighand(p, &flags);
		if (unlikely(sighand == NULL)) {
			/*
			 * The process has been reaped.
			 * We can't even collect a sample any more.
			 */
			cpu_timer_setexpires(ctmr, 0);
			return;
		} else if (unlikely(p->exit_state) && thread_group_empty(p)) {
			/* If the process is dying, no need to rearm */
			goto unlock;
		}
		now = cpu_clock_sample_group(clkid, p, true);
		bump_cpu_timer(timer, now);
		/* Leave the sighand locked for the call below.  */
	}

	/*
	 * Now re-arm for the new expiry time.
	 */
	arm_timer(timer);
unlock:
	unlock_task_sighand(p, &flags);
}