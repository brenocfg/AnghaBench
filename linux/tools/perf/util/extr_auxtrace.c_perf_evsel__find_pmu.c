#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_pmu {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;

/* Variables and functions */
 struct perf_pmu* perf_pmu__scan (struct perf_pmu*) ; 

__attribute__((used)) static struct perf_pmu *perf_evsel__find_pmu(struct evsel *evsel)
{
	struct perf_pmu *pmu = NULL;

	while ((pmu = perf_pmu__scan(pmu)) != NULL) {
		if (pmu->type == evsel->core.attr.type)
			break;
	}

	return pmu;
}