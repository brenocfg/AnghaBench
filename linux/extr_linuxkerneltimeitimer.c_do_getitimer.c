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
struct task_struct {TYPE_1__* sighand; TYPE_2__* signal; } ;
struct itimerval {int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  it_real_incr; int /*<<< orphan*/  real_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUCLOCK_PROF ; 
 int /*<<< orphan*/  CPUCLOCK_VIRT ; 
 int EINVAL ; 
#define  ITIMER_PROF 130 
#define  ITIMER_REAL 129 
#define  ITIMER_VIRTUAL 128 
 struct task_struct* current ; 
 int /*<<< orphan*/  get_cpu_itimer (struct task_struct*,int /*<<< orphan*/ ,struct itimerval*) ; 
 int /*<<< orphan*/  itimer_get_remtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_to_timeval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int do_getitimer(int which, struct itimerval *value)
{
	struct task_struct *tsk = current;

	switch (which) {
	case ITIMER_REAL:
		spin_lock_irq(&tsk->sighand->siglock);
		value->it_value = itimer_get_remtime(&tsk->signal->real_timer);
		value->it_interval =
			ktime_to_timeval(tsk->signal->it_real_incr);
		spin_unlock_irq(&tsk->sighand->siglock);
		break;
	case ITIMER_VIRTUAL:
		get_cpu_itimer(tsk, CPUCLOCK_VIRT, value);
		break;
	case ITIMER_PROF:
		get_cpu_itimer(tsk, CPUCLOCK_PROF, value);
		break;
	default:
		return(-EINVAL);
	}
	return 0;
}