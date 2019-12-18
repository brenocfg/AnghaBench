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
struct perf_event {scalar_t__ pmu; int cpu; } ;

/* Variables and functions */

__attribute__((used)) static bool exclusive_event_match(struct perf_event *e1, struct perf_event *e2)
{
	if ((e1->pmu == e2->pmu) &&
	    (e1->cpu == e2->cpu ||
	     e1->cpu == -1 ||
	     e2->cpu == -1))
		return true;
	return false;
}