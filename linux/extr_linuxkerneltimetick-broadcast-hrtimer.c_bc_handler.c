#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;
struct TYPE_4__ {scalar_t__ next_event; int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int HRTIMER_NORESTART ; 
 int HRTIMER_RESTART ; 
 scalar_t__ KTIME_MAX ; 
 TYPE_1__ ce_broadcast_hrtimer ; 
 scalar_t__ clockevent_state_oneshot (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static enum hrtimer_restart bc_handler(struct hrtimer *t)
{
	ce_broadcast_hrtimer.event_handler(&ce_broadcast_hrtimer);

	if (clockevent_state_oneshot(&ce_broadcast_hrtimer))
		if (ce_broadcast_hrtimer.next_event != KTIME_MAX)
			return HRTIMER_RESTART;

	return HRTIMER_NORESTART;
}