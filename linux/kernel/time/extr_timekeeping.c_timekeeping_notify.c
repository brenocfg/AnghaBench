#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct clocksource* clock; } ;
struct timekeeper {TYPE_1__ tkr_mono; } ;
struct clocksource {int dummy; } ;
struct TYPE_4__ {struct timekeeper timekeeper; } ;

/* Variables and functions */
 int /*<<< orphan*/  change_clocksource ; 
 int /*<<< orphan*/  stop_machine (int /*<<< orphan*/ ,struct clocksource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_clock_notify () ; 
 TYPE_2__ tk_core ; 

int timekeeping_notify(struct clocksource *clock)
{
	struct timekeeper *tk = &tk_core.timekeeper;

	if (tk->tkr_mono.clock == clock)
		return 0;
	stop_machine(change_clocksource, clock, NULL);
	tick_clock_notify();
	return tk->tkr_mono.clock == clock ? 0 : -1;
}