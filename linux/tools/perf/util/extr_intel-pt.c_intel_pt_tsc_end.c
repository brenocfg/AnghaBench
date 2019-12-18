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
typedef  scalar_t__ u64 ;
struct intel_pt {int /*<<< orphan*/  tc; } ;

/* Variables and functions */
 scalar_t__ perf_time_to_tsc (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ tsc_to_perf_time (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 intel_pt_tsc_end(u64 ns, struct intel_pt *pt)
{
	u64 tsc, tm;

	tsc = perf_time_to_tsc(ns, &pt->tc);

	while (1) {
		tm = tsc_to_perf_time(tsc, &pt->tc);
		if (tm > ns)
			break;
		tsc += 1;
	}

	while (tm > ns)
		tm = tsc_to_perf_time(--tsc, &pt->tc);

	return tsc;
}