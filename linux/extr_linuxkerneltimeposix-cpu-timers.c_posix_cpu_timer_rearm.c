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
typedef  int /*<<< orphan*/  u64 ;
struct task_struct {int /*<<< orphan*/  exit_state; } ;
struct sighand_struct {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; struct task_struct* task; } ;
struct TYPE_4__ {TYPE_1__ cpu; } ;
struct k_itimer {int /*<<< orphan*/  it_clock; TYPE_2__ it; } ;

/* Variables and functions */
 scalar_t__ CPUCLOCK_PERTHREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_timer (struct k_itimer*) ; 
 int /*<<< orphan*/  bump_cpu_timer (struct k_itimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_clock_sample (int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_timer_sample_group (int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ *) ; 
 struct sighand_struct* lock_task_sighand (struct task_struct*,unsigned long*) ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static void posix_cpu_timer_rearm(struct k_itimer *timer)
{
	struct sighand_struct *sighand;
	unsigned long flags;
	struct task_struct *p = timer->it.cpu.task;
	u64 now;

	WARN_ON_ONCE(p == NULL);

	/*
	 * Fetch the current sample and update the timer's expiry time.
	 */
	if (CPUCLOCK_PERTHREAD(timer->it_clock)) {
		cpu_clock_sample(timer->it_clock, p, &now);
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
			timer->it.cpu.expires = 0;
			return;
		} else if (unlikely(p->exit_state) && thread_group_empty(p)) {
			/* If the process is dying, no need to rearm */
			goto unlock;
		}
		cpu_timer_sample_group(timer->it_clock, p, &now);
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