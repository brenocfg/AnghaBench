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
struct hrtimer_clock_base {int /*<<< orphan*/  (* get_time ) () ;} ;
struct hrtimer {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;

/* Variables and functions */
 int const HRTIMER_MODE_PINNED ; 
 int const HRTIMER_MODE_REL ; 
 int enqueue_hrtimer (struct hrtimer*,struct hrtimer_clock_base*,int const) ; 
 int /*<<< orphan*/  hrtimer_set_expires_range_ns (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_update_lowres (struct hrtimer*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ktime_add_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_hrtimer (struct hrtimer*,struct hrtimer_clock_base*,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 struct hrtimer_clock_base* switch_hrtimer_base (struct hrtimer*,struct hrtimer_clock_base*,int const) ; 

__attribute__((used)) static int __hrtimer_start_range_ns(struct hrtimer *timer, ktime_t tim,
				    u64 delta_ns, const enum hrtimer_mode mode,
				    struct hrtimer_clock_base *base)
{
	struct hrtimer_clock_base *new_base;

	/* Remove an active timer from the queue: */
	remove_hrtimer(timer, base, true);

	if (mode & HRTIMER_MODE_REL)
		tim = ktime_add_safe(tim, base->get_time());

	tim = hrtimer_update_lowres(timer, tim, mode);

	hrtimer_set_expires_range_ns(timer, tim, delta_ns);

	/* Switch the timer base, if necessary: */
	new_base = switch_hrtimer_base(timer, base, mode & HRTIMER_MODE_PINNED);

	return enqueue_hrtimer(timer, new_base, mode);
}