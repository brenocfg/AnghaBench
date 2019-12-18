#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct timecounter {int cycle_last; int /*<<< orphan*/  frac; int /*<<< orphan*/  mask; TYPE_1__* cc; } ;
struct TYPE_3__ {int (* read ) (TYPE_1__*) ;int mask; } ;

/* Variables and functions */
 int cyclecounter_cyc2ns (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static u64 timecounter_read_delta(struct timecounter *tc)
{
	u64 cycle_now, cycle_delta;
	u64 ns_offset;

	/* read cycle counter: */
	cycle_now = tc->cc->read(tc->cc);

	/* calculate the delta since the last timecounter_read_delta(): */
	cycle_delta = (cycle_now - tc->cycle_last) & tc->cc->mask;

	/* convert to nanoseconds: */
	ns_offset = cyclecounter_cyc2ns(tc->cc, cycle_delta,
					tc->mask, &tc->frac);

	/* update time stamp of timecounter_read_delta() call: */
	tc->cycle_last = cycle_now;

	return ns_offset;
}