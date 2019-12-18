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
typedef  void* timer_t ;
struct k_itimer {int /*<<< orphan*/  it_id; int /*<<< orphan*/  kclock; } ;
struct k_clock {int /*<<< orphan*/  (* timer_wait_running ) (struct k_itimer*) ;} ;

/* Variables and functions */
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct k_itimer* lock_timer (void*,unsigned long*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct k_itimer*) ; 
 int /*<<< orphan*/  unlock_timer (struct k_itimer*,unsigned long) ; 

__attribute__((used)) static struct k_itimer *timer_wait_running(struct k_itimer *timer,
					   unsigned long *flags)
{
	const struct k_clock *kc = READ_ONCE(timer->kclock);
	timer_t timer_id = READ_ONCE(timer->it_id);

	/* Prevent kfree(timer) after dropping the lock */
	rcu_read_lock();
	unlock_timer(timer, *flags);

	if (!WARN_ON_ONCE(!kc->timer_wait_running))
		kc->timer_wait_running(timer);

	rcu_read_unlock();
	/* Relock the timer. It might be not longer hashed. */
	return lock_timer(timer_id, flags);
}