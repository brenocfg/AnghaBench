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
struct hrtimer_cpu_base {unsigned int active_bases; struct hrtimer* next_timer; struct hrtimer* softirq_next_timer; int /*<<< orphan*/  softirq_activated; } ;
struct hrtimer {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 unsigned int HRTIMER_ACTIVE_HARD ; 
 unsigned int HRTIMER_ACTIVE_SOFT ; 
 int /*<<< orphan*/  KTIME_MAX ; 
 int /*<<< orphan*/  __hrtimer_next_event_base (struct hrtimer_cpu_base*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t
__hrtimer_get_next_event(struct hrtimer_cpu_base *cpu_base, unsigned int active_mask)
{
	unsigned int active;
	struct hrtimer *next_timer = NULL;
	ktime_t expires_next = KTIME_MAX;

	if (!cpu_base->softirq_activated && (active_mask & HRTIMER_ACTIVE_SOFT)) {
		active = cpu_base->active_bases & HRTIMER_ACTIVE_SOFT;
		cpu_base->softirq_next_timer = NULL;
		expires_next = __hrtimer_next_event_base(cpu_base, NULL,
							 active, KTIME_MAX);

		next_timer = cpu_base->softirq_next_timer;
	}

	if (active_mask & HRTIMER_ACTIVE_HARD) {
		active = cpu_base->active_bases & HRTIMER_ACTIVE_HARD;
		cpu_base->next_timer = next_timer;
		expires_next = __hrtimer_next_event_base(cpu_base, NULL, active,
							 expires_next);
	}

	return expires_next;
}