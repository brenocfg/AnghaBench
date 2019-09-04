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
typedef  unsigned long u64 ;
typedef  int u32 ;
struct TYPE_2__ {unsigned long prev; unsigned long interval; int prev_window; unsigned long current_rate; unsigned long rate; unsigned long credit; unsigned long credit_cap; } ;
struct dsthash_ent {TYPE_1__ rateinfo; } ;

/* Variables and functions */
 unsigned long CREDITS_PER_JIFFY ; 
 unsigned long CREDITS_PER_JIFFY_BYTES ; 
 unsigned long CREDITS_PER_JIFFY_v1 ; 
 unsigned long HZ ; 
 int XT_HASHLIMIT_BYTES ; 
 int XT_HASHLIMIT_RATE_MATCH ; 

__attribute__((used)) static void rateinfo_recalc(struct dsthash_ent *dh, unsigned long now,
			    u32 mode, int revision)
{
	unsigned long delta = now - dh->rateinfo.prev;
	u64 cap, cpj;

	if (delta == 0)
		return;

	if (revision >= 3 && mode & XT_HASHLIMIT_RATE_MATCH) {
		u64 interval = dh->rateinfo.interval * HZ;

		if (delta < interval)
			return;

		dh->rateinfo.prev = now;
		dh->rateinfo.prev_window =
			((dh->rateinfo.current_rate * interval) >
			 (delta * dh->rateinfo.rate));
		dh->rateinfo.current_rate = 0;

		return;
	}

	dh->rateinfo.prev = now;

	if (mode & XT_HASHLIMIT_BYTES) {
		u64 tmp = dh->rateinfo.credit;
		dh->rateinfo.credit += CREDITS_PER_JIFFY_BYTES * delta;
		cap = CREDITS_PER_JIFFY_BYTES * HZ;
		if (tmp >= dh->rateinfo.credit) {/* overflow */
			dh->rateinfo.credit = cap;
			return;
		}
	} else {
		cpj = (revision == 1) ?
			CREDITS_PER_JIFFY_v1 : CREDITS_PER_JIFFY;
		dh->rateinfo.credit += delta * cpj;
		cap = dh->rateinfo.credit_cap;
	}
	if (dh->rateinfo.credit > cap)
		dh->rateinfo.credit = cap;
}