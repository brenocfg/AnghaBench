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
struct tk_read_base {int /*<<< orphan*/  clock; } ;
struct clocksource {int /*<<< orphan*/  (* read ) (struct clocksource*) ;} ;

/* Variables and functions */
 struct clocksource* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clocksource*) ; 

__attribute__((used)) static inline u64 tk_clock_read(const struct tk_read_base *tkr)
{
	struct clocksource *clock = READ_ONCE(tkr->clock);

	return clock->read(clock);
}