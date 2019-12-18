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
typedef  int /*<<< orphan*/  u8 ;
struct hrtimer_clock_base {scalar_t__ cpu_base; } ;
struct hrtimer {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_STATE_INACTIVE ; 
 int /*<<< orphan*/  __remove_hrtimer (struct hrtimer*,struct hrtimer_clock_base*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_deactivate (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_bases ; 
 scalar_t__ hrtimer_is_queued (struct hrtimer*) ; 
 scalar_t__ this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
remove_hrtimer(struct hrtimer *timer, struct hrtimer_clock_base *base, bool restart)
{
	if (hrtimer_is_queued(timer)) {
		u8 state = timer->state;
		int reprogram;

		/*
		 * Remove the timer and force reprogramming when high
		 * resolution mode is active and the timer is on the current
		 * CPU. If we remove a timer on another CPU, reprogramming is
		 * skipped. The interrupt event on this CPU is fired and
		 * reprogramming happens in the interrupt handler. This is a
		 * rare case and less expensive than a smp call.
		 */
		debug_deactivate(timer);
		reprogram = base->cpu_base == this_cpu_ptr(&hrtimer_bases);

		if (!restart)
			state = HRTIMER_STATE_INACTIVE;

		__remove_hrtimer(timer, base, state, reprogram);
		return 1;
	}
	return 0;
}