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
struct timecounter {int cycle_last; int nsec; int frac; int /*<<< orphan*/  mask; TYPE_1__* cc; } ;
struct TYPE_3__ {int mask; } ;

/* Variables and functions */
 scalar_t__ cc_cyc2ns_backwards (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cyclecounter_cyc2ns (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 

u64 timecounter_cyc2time(struct timecounter *tc,
			 u64 cycle_tstamp)
{
	u64 delta = (cycle_tstamp - tc->cycle_last) & tc->cc->mask;
	u64 nsec = tc->nsec, frac = tc->frac;

	/*
	 * Instead of always treating cycle_tstamp as more recent
	 * than tc->cycle_last, detect when it is too far in the
	 * future and treat it as old time stamp instead.
	 */
	if (delta > tc->cc->mask / 2) {
		delta = (tc->cycle_last - cycle_tstamp) & tc->cc->mask;
		nsec -= cc_cyc2ns_backwards(tc->cc, delta, tc->mask, frac);
	} else {
		nsec += cyclecounter_cyc2ns(tc->cc, delta, tc->mask, &frac);
	}

	return nsec;
}