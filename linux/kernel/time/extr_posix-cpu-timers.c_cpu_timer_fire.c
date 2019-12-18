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
struct cpu_timer {int dummy; } ;
struct TYPE_2__ {struct cpu_timer cpu; } ;
struct k_itimer {int it_sigev_notify; int /*<<< orphan*/  it_requeue_pending; int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_process; int /*<<< orphan*/ * sigq; TYPE_1__ it; } ;

/* Variables and functions */
 int SIGEV_NONE ; 
 int SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  cpu_timer_setexpires (struct cpu_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_cpu_timer_rearm (struct k_itimer*) ; 
 scalar_t__ posix_timer_event (struct k_itimer*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_timer_fire(struct k_itimer *timer)
{
	struct cpu_timer *ctmr = &timer->it.cpu;

	if ((timer->it_sigev_notify & ~SIGEV_THREAD_ID) == SIGEV_NONE) {
		/*
		 * User don't want any signal.
		 */
		cpu_timer_setexpires(ctmr, 0);
	} else if (unlikely(timer->sigq == NULL)) {
		/*
		 * This a special case for clock_nanosleep,
		 * not a normal timer from sys_timer_create.
		 */
		wake_up_process(timer->it_process);
		cpu_timer_setexpires(ctmr, 0);
	} else if (!timer->it_interval) {
		/*
		 * One-shot timer.  Clear it as soon as it's fired.
		 */
		posix_timer_event(timer, 0);
		cpu_timer_setexpires(ctmr, 0);
	} else if (posix_timer_event(timer, ++timer->it_requeue_pending)) {
		/*
		 * The signal did not get queued because the signal
		 * was ignored, so we won't get any callback to
		 * reload the timer.  But we need to keep it
		 * ticking in case the signal is deliverable next time.
		 */
		posix_cpu_timer_rearm(timer);
		++timer->it_requeue_pending;
	}
}