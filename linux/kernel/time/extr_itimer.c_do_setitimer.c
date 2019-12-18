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
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct itimerval {int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_value; } ;
struct hrtimer {int dummy; } ;
typedef  void* ktime_t ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {void* it_real_incr; struct hrtimer real_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUCLOCK_PROF ; 
 int /*<<< orphan*/  CPUCLOCK_VIRT ; 
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
#define  ITIMER_PROF 130 
#define  ITIMER_REAL 129 
#define  ITIMER_VIRTUAL 128 
 struct task_struct* current ; 
 int /*<<< orphan*/  hrtimer_cancel_wait_running (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_start (struct hrtimer*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_try_to_cancel (struct hrtimer*) ; 
 int /*<<< orphan*/  itimer_get_remtime (struct hrtimer*) ; 
 int /*<<< orphan*/  ktime_to_timeval (void*) ; 
 int /*<<< orphan*/  set_cpu_itimer (struct task_struct*,int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 void* timeval_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeval_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_itimer_state (int const,struct itimerval*,int /*<<< orphan*/ ) ; 

int do_setitimer(int which, struct itimerval *value, struct itimerval *ovalue)
{
	struct task_struct *tsk = current;
	struct hrtimer *timer;
	ktime_t expires;

	/*
	 * Validate the timevals in value.
	 */
	if (!timeval_valid(&value->it_value) ||
	    !timeval_valid(&value->it_interval))
		return -EINVAL;

	switch (which) {
	case ITIMER_REAL:
again:
		spin_lock_irq(&tsk->sighand->siglock);
		timer = &tsk->signal->real_timer;
		if (ovalue) {
			ovalue->it_value = itimer_get_remtime(timer);
			ovalue->it_interval
				= ktime_to_timeval(tsk->signal->it_real_incr);
		}
		/* We are sharing ->siglock with it_real_fn() */
		if (hrtimer_try_to_cancel(timer) < 0) {
			spin_unlock_irq(&tsk->sighand->siglock);
			hrtimer_cancel_wait_running(timer);
			goto again;
		}
		expires = timeval_to_ktime(value->it_value);
		if (expires != 0) {
			tsk->signal->it_real_incr =
				timeval_to_ktime(value->it_interval);
			hrtimer_start(timer, expires, HRTIMER_MODE_REL);
		} else
			tsk->signal->it_real_incr = 0;

		trace_itimer_state(ITIMER_REAL, value, 0);
		spin_unlock_irq(&tsk->sighand->siglock);
		break;
	case ITIMER_VIRTUAL:
		set_cpu_itimer(tsk, CPUCLOCK_VIRT, value, ovalue);
		break;
	case ITIMER_PROF:
		set_cpu_itimer(tsk, CPUCLOCK_PROF, value, ovalue);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}