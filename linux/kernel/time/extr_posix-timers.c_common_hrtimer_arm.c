#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hrtimer {TYPE_1__* base; int /*<<< orphan*/  function; } ;
struct TYPE_6__ {struct hrtimer timer; } ;
struct TYPE_5__ {TYPE_3__ real; } ;
struct k_itimer {scalar_t__ it_clock; TYPE_2__ it; int /*<<< orphan*/ * kclock; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_time ) () ;} ;

/* Variables and functions */
 scalar_t__ CLOCK_REALTIME ; 
 int HRTIMER_MODE_ABS ; 
 int HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  clock_monotonic ; 
 int /*<<< orphan*/  clock_realtime ; 
 int /*<<< orphan*/  hrtimer_init (struct hrtimer*,scalar_t__,int) ; 
 int /*<<< orphan*/  hrtimer_set_expires (struct hrtimer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start_expires (struct hrtimer*,int) ; 
 int /*<<< orphan*/  ktime_add_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_timer_fn ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void common_hrtimer_arm(struct k_itimer *timr, ktime_t expires,
			       bool absolute, bool sigev_none)
{
	struct hrtimer *timer = &timr->it.real.timer;
	enum hrtimer_mode mode;

	mode = absolute ? HRTIMER_MODE_ABS : HRTIMER_MODE_REL;
	/*
	 * Posix magic: Relative CLOCK_REALTIME timers are not affected by
	 * clock modifications, so they become CLOCK_MONOTONIC based under the
	 * hood. See hrtimer_init(). Update timr->kclock, so the generic
	 * functions which use timr->kclock->clock_get() work.
	 *
	 * Note: it_clock stays unmodified, because the next timer_set() might
	 * use ABSTIME, so it needs to switch back.
	 */
	if (timr->it_clock == CLOCK_REALTIME)
		timr->kclock = absolute ? &clock_realtime : &clock_monotonic;

	hrtimer_init(&timr->it.real.timer, timr->it_clock, mode);
	timr->it.real.timer.function = posix_timer_fn;

	if (!absolute)
		expires = ktime_add_safe(expires, timer->base->get_time());
	hrtimer_set_expires(timer, expires);

	if (!sigev_none)
		hrtimer_start_expires(timer, HRTIMER_MODE_ABS);
}