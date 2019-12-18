#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ is_hard; } ;
struct hrtimer_sleeper {TYPE_1__ timer; } ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPT_RT ; 
 int HRTIMER_MODE_HARD ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start_expires (TYPE_1__*,int) ; 

void hrtimer_sleeper_start_expires(struct hrtimer_sleeper *sl,
				   enum hrtimer_mode mode)
{
	/*
	 * Make the enqueue delivery mode check work on RT. If the sleeper
	 * was initialized for hard interrupt delivery, force the mode bit.
	 * This is a special case for hrtimer_sleepers because
	 * hrtimer_init_sleeper() determines the delivery mode on RT so the
	 * fiddling with this decision is avoided at the call sites.
	 */
	if (IS_ENABLED(CONFIG_PREEMPT_RT) && sl->timer.is_hard)
		mode |= HRTIMER_MODE_HARD;

	hrtimer_start_expires(&sl->timer, mode);
}