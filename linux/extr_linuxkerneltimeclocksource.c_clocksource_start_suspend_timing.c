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
typedef  int /*<<< orphan*/  u64 ;
struct clocksource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (TYPE_1__*) ;scalar_t__ (* enable ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ clocksource_is_suspend (struct clocksource*) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 TYPE_1__* suspend_clocksource ; 
 int /*<<< orphan*/  suspend_start ; 

void clocksource_start_suspend_timing(struct clocksource *cs, u64 start_cycles)
{
	if (!suspend_clocksource)
		return;

	/*
	 * If current clocksource is the suspend timer, we should use the
	 * tkr_mono.cycle_last value as suspend_start to avoid same reading
	 * from suspend timer.
	 */
	if (clocksource_is_suspend(cs)) {
		suspend_start = start_cycles;
		return;
	}

	if (suspend_clocksource->enable &&
	    suspend_clocksource->enable(suspend_clocksource)) {
		pr_warn_once("Failed to enable the non-suspend-able clocksource.\n");
		return;
	}

	suspend_start = suspend_clocksource->read(suspend_clocksource);
}