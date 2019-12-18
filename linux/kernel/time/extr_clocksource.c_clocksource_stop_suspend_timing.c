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
typedef  scalar_t__ u64 ;
struct clocksource {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* read ) (TYPE_1__*) ;int /*<<< orphan*/  (* disable ) (TYPE_1__*) ;int /*<<< orphan*/  shift; int /*<<< orphan*/  mult; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ clocksource_delta (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ clocksource_is_suspend (struct clocksource*) ; 
 scalar_t__ mul_u64_u32_shr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 TYPE_1__* suspend_clocksource ; 
 scalar_t__ suspend_start ; 

u64 clocksource_stop_suspend_timing(struct clocksource *cs, u64 cycle_now)
{
	u64 now, delta, nsec = 0;

	if (!suspend_clocksource)
		return 0;

	/*
	 * If current clocksource is the suspend timer, we should use the
	 * tkr_mono.cycle_last value from timekeeping as current cycle to
	 * avoid same reading from suspend timer.
	 */
	if (clocksource_is_suspend(cs))
		now = cycle_now;
	else
		now = suspend_clocksource->read(suspend_clocksource);

	if (now > suspend_start) {
		delta = clocksource_delta(now, suspend_start,
					  suspend_clocksource->mask);
		nsec = mul_u64_u32_shr(delta, suspend_clocksource->mult,
				       suspend_clocksource->shift);
	}

	/*
	 * Disable the suspend timer to save power if current clocksource is
	 * not the suspend timer.
	 */
	if (!clocksource_is_suspend(cs) && suspend_clocksource->disable)
		suspend_clocksource->disable(suspend_clocksource);

	return nsec;
}