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
struct perf_tsc_conversion {int time_shift; int time_zero; int time_mult; } ;

/* Variables and functions */

u64 tsc_to_perf_time(u64 cyc, struct perf_tsc_conversion *tc)
{
	u64 quot, rem;

	quot = cyc >> tc->time_shift;
	rem  = cyc & (((u64)1 << tc->time_shift) - 1);
	return tc->time_zero + quot * tc->time_mult +
	       ((rem * tc->time_mult) >> tc->time_shift);
}