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
struct perf_sched {scalar_t__ run_measurement_overhead; } ;

/* Variables and functions */
 scalar_t__ get_nsecs () ; 

__attribute__((used)) static void burn_nsecs(struct perf_sched *sched, u64 nsecs)
{
	u64 T0 = get_nsecs(), T1;

	do {
		T1 = get_nsecs();
	} while (T1 + sched->run_measurement_overhead < T0 + nsecs);
}