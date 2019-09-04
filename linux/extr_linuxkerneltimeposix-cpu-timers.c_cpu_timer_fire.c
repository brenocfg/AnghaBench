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
struct TYPE_4__ {scalar_t__ incr; scalar_t__ expires; } ;
struct TYPE_3__ {TYPE_2__ cpu; } ;
struct k_itimer {int it_sigev_notify; int /*<<< orphan*/  it_requeue_pending; TYPE_1__ it; int /*<<< orphan*/  it_process; int /*<<< orphan*/ * sigq; } ;

/* Variables and functions */
 int SIGEV_NONE ; 
 int SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  posix_cpu_timer_rearm (struct k_itimer*) ; 
 scalar_t__ posix_timer_event (struct k_itimer*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_timer_fire(struct k_itimer *timer)
{
	if ((timer->it_sigev_notify & ~SIGEV_THREAD_ID) == SIGEV_NONE) {
		/*
		 * User don't want any signal.
		 */
		timer->it.cpu.expires = 0;
	} else if (unlikely(timer->sigq == NULL)) {
		/*
		 * This a special case for clock_nanosleep,
		 * not a normal timer from sys_timer_create.
		 */
		wake_up_process(timer->it_process);
		timer->it.cpu.expires = 0;
	} else if (timer->it.cpu.incr == 0) {
		/*
		 * One-shot timer.  Clear it as soon as it's fired.
		 */
		posix_timer_event(timer, 0);
		timer->it.cpu.expires = 0;
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