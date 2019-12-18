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
typedef  int /*<<< orphan*/  u64 ;
struct hrtimer_clock_base {int dummy; } ;
struct hrtimer {int /*<<< orphan*/  is_hard; int /*<<< orphan*/  is_soft; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPT_RT ; 
 int const HRTIMER_MODE_HARD ; 
 int const HRTIMER_MODE_SOFT ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ __hrtimer_start_range_ns (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,struct hrtimer_clock_base*) ; 
 int /*<<< orphan*/  hrtimer_reprogram (struct hrtimer*,int) ; 
 struct hrtimer_clock_base* lock_hrtimer_base (struct hrtimer*,unsigned long*) ; 
 int /*<<< orphan*/  unlock_hrtimer_base (struct hrtimer*,unsigned long*) ; 

void hrtimer_start_range_ns(struct hrtimer *timer, ktime_t tim,
			    u64 delta_ns, const enum hrtimer_mode mode)
{
	struct hrtimer_clock_base *base;
	unsigned long flags;

	/*
	 * Check whether the HRTIMER_MODE_SOFT bit and hrtimer.is_soft
	 * match on CONFIG_PREEMPT_RT = n. With PREEMPT_RT check the hard
	 * expiry mode because unmarked timers are moved to softirq expiry.
	 */
	if (!IS_ENABLED(CONFIG_PREEMPT_RT))
		WARN_ON_ONCE(!(mode & HRTIMER_MODE_SOFT) ^ !timer->is_soft);
	else
		WARN_ON_ONCE(!(mode & HRTIMER_MODE_HARD) ^ !timer->is_hard);

	base = lock_hrtimer_base(timer, &flags);

	if (__hrtimer_start_range_ns(timer, tim, delta_ns, mode, base))
		hrtimer_reprogram(timer, true);

	unlock_hrtimer_base(timer, &flags);
}