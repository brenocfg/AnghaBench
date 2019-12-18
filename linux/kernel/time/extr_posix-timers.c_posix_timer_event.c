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
struct k_itimer {int it_sigev_notify; int /*<<< orphan*/  it_pid; TYPE_2__* sigq; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;
struct TYPE_3__ {int si_sys_private; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 int PIDTYPE_PID ; 
 int PIDTYPE_TGID ; 
 int SIGEV_THREAD_ID ; 
 int send_sigqueue (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int posix_timer_event(struct k_itimer *timr, int si_private)
{
	enum pid_type type;
	int ret = -1;
	/*
	 * FIXME: if ->sigq is queued we can race with
	 * dequeue_signal()->posixtimer_rearm().
	 *
	 * If dequeue_signal() sees the "right" value of
	 * si_sys_private it calls posixtimer_rearm().
	 * We re-queue ->sigq and drop ->it_lock().
	 * posixtimer_rearm() locks the timer
	 * and re-schedules it while ->sigq is pending.
	 * Not really bad, but not that we want.
	 */
	timr->sigq->info.si_sys_private = si_private;

	type = !(timr->it_sigev_notify & SIGEV_THREAD_ID) ? PIDTYPE_TGID : PIDTYPE_PID;
	ret = send_sigqueue(timr->sigq, timr->it_pid, type);
	/* If we failed to send the signal the timer stops. */
	return ret > 0;
}