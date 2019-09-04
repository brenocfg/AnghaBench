#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct k_itimer {scalar_t__ it_active; scalar_t__ it_interval; struct k_clock* kclock; } ;
struct k_clock {scalar_t__ (* timer_try_to_cancel ) (struct k_itimer*) ;} ;

/* Variables and functions */
 int TIMER_RETRY ; 
 scalar_t__ stub1 (struct k_itimer*) ; 

int common_timer_del(struct k_itimer *timer)
{
	const struct k_clock *kc = timer->kclock;

	timer->it_interval = 0;
	if (kc->timer_try_to_cancel(timer) < 0)
		return TIMER_RETRY;
	timer->it_active = 0;
	return 0;
}