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
struct tk_read_base {int /*<<< orphan*/  mask; int /*<<< orphan*/  cycle_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  clocksource_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tk_clock_read (struct tk_read_base const*) ; 

__attribute__((used)) static inline u64 timekeeping_get_delta(const struct tk_read_base *tkr)
{
	u64 cycle_now, delta;

	/* read clocksource */
	cycle_now = tk_clock_read(tkr);

	/* calculate the delta since the last update_wall_time */
	delta = clocksource_delta(cycle_now, tkr->cycle_last, tkr->mask);

	return delta;
}