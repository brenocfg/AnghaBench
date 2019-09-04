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
struct timeval {int dummy; } ;
struct hrtimer {int dummy; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_USEC ; 
 scalar_t__ __hrtimer_get_remaining (struct hrtimer*,int) ; 
 scalar_t__ hrtimer_active (struct hrtimer*) ; 
 struct timeval ktime_to_timeval (scalar_t__) ; 

__attribute__((used)) static struct timeval itimer_get_remtime(struct hrtimer *timer)
{
	ktime_t rem = __hrtimer_get_remaining(timer, true);

	/*
	 * Racy but safe: if the itimer expires after the above
	 * hrtimer_get_remtime() call but before this condition
	 * then we return 0 - which is correct.
	 */
	if (hrtimer_active(timer)) {
		if (rem <= 0)
			rem = NSEC_PER_USEC;
	} else
		rem = 0;

	return ktime_to_timeval(rem);
}