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
struct hrtimer_cpu_base {int /*<<< orphan*/  softirq_next_timer; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_ACTIVE_SOFT ; 
 scalar_t__ KTIME_MAX ; 
 scalar_t__ __hrtimer_get_next_event (struct hrtimer_cpu_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_reprogram (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hrtimer_update_softirq_timer(struct hrtimer_cpu_base *cpu_base, bool reprogram)
{
	ktime_t expires;

	/*
	 * Find the next SOFT expiration.
	 */
	expires = __hrtimer_get_next_event(cpu_base, HRTIMER_ACTIVE_SOFT);

	/*
	 * reprogramming needs to be triggered, even if the next soft
	 * hrtimer expires at the same time than the next hard
	 * hrtimer. cpu_base->softirq_expires_next needs to be updated!
	 */
	if (expires == KTIME_MAX)
		return;

	/*
	 * cpu_base->*next_timer is recomputed by __hrtimer_get_next_event()
	 * cpu_base->*expires_next is only set by hrtimer_reprogram()
	 */
	hrtimer_reprogram(cpu_base->softirq_next_timer, reprogram);
}