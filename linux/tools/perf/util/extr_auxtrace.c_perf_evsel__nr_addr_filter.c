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
struct perf_pmu {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 struct perf_pmu* perf_evsel__find_pmu (struct evsel*) ; 
 int /*<<< orphan*/  perf_pmu__scan_file (struct perf_pmu*,char*,char*,int*) ; 

__attribute__((used)) static int perf_evsel__nr_addr_filter(struct evsel *evsel)
{
	struct perf_pmu *pmu = perf_evsel__find_pmu(evsel);
	int nr_addr_filters = 0;

	if (!pmu)
		return 0;

	perf_pmu__scan_file(pmu, "nr_addr_filters", "%d", &nr_addr_filters);

	return nr_addr_filters;
}