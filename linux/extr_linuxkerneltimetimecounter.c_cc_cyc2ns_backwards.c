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
typedef  int u64 ;
struct cyclecounter {int mult; int shift; } ;

/* Variables and functions */

__attribute__((used)) static u64 cc_cyc2ns_backwards(const struct cyclecounter *cc,
			       u64 cycles, u64 mask, u64 frac)
{
	u64 ns = (u64) cycles;

	ns = ((ns * cc->mult) - frac) >> cc->shift;

	return ns;
}