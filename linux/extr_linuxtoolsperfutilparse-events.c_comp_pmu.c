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
struct perf_pmu_event_symbol {int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comp_pmu(const void *p1, const void *p2)
{
	struct perf_pmu_event_symbol *pmu1 = (struct perf_pmu_event_symbol *) p1;
	struct perf_pmu_event_symbol *pmu2 = (struct perf_pmu_event_symbol *) p2;

	return strcasecmp(pmu1->symbol, pmu2->symbol);
}