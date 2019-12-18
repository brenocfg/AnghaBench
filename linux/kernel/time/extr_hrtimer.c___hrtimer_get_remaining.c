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
struct hrtimer {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TIME_LOW_RES ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_expires_remaining (struct hrtimer const*) ; 
 int /*<<< orphan*/  hrtimer_expires_remaining_adjusted (struct hrtimer const*) ; 
 int /*<<< orphan*/  lock_hrtimer_base (struct hrtimer const*,unsigned long*) ; 
 int /*<<< orphan*/  unlock_hrtimer_base (struct hrtimer const*,unsigned long*) ; 

ktime_t __hrtimer_get_remaining(const struct hrtimer *timer, bool adjust)
{
	unsigned long flags;
	ktime_t rem;

	lock_hrtimer_base(timer, &flags);
	if (IS_ENABLED(CONFIG_TIME_LOW_RES) && adjust)
		rem = hrtimer_expires_remaining_adjusted(timer);
	else
		rem = hrtimer_expires_remaining(timer);
	unlock_hrtimer_base(timer, &flags);

	return rem;
}