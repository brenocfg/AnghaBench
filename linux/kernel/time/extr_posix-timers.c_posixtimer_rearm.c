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
struct kernel_siginfo {scalar_t__ si_sys_private; int /*<<< orphan*/  si_overrun; int /*<<< orphan*/  si_tid; } ;
struct k_itimer {scalar_t__ it_requeue_pending; int it_active; long long it_overrun_last; long long it_overrun; TYPE_1__* kclock; scalar_t__ it_interval; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* timer_rearm ) (struct k_itimer*) ;} ;

/* Variables and functions */
 struct k_itimer* lock_timer (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (struct k_itimer*) ; 
 int /*<<< orphan*/  timer_overrun_to_int (struct k_itimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_timer (struct k_itimer*,unsigned long) ; 

void posixtimer_rearm(struct kernel_siginfo *info)
{
	struct k_itimer *timr;
	unsigned long flags;

	timr = lock_timer(info->si_tid, &flags);
	if (!timr)
		return;

	if (timr->it_interval && timr->it_requeue_pending == info->si_sys_private) {
		timr->kclock->timer_rearm(timr);

		timr->it_active = 1;
		timr->it_overrun_last = timr->it_overrun;
		timr->it_overrun = -1LL;
		++timr->it_requeue_pending;

		info->si_overrun = timer_overrun_to_int(timr, info->si_overrun);
	}

	unlock_timer(timr, flags);
}