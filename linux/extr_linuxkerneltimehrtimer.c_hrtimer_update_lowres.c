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
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;

/* Variables and functions */

__attribute__((used)) static inline ktime_t hrtimer_update_lowres(struct hrtimer *timer, ktime_t tim,
					    const enum hrtimer_mode mode)
{
#ifdef CONFIG_TIME_LOW_RES
	/*
	 * CONFIG_TIME_LOW_RES indicates that the system has no way to return
	 * granular time values. For relative timers we add hrtimer_resolution
	 * (i.e. one jiffie) to prevent short timeouts.
	 */
	timer->is_rel = mode & HRTIMER_MODE_REL;
	if (timer->is_rel)
		tim = ktime_add_safe(tim, hrtimer_resolution);
#endif
	return tim;
}