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
struct perf_pmu_event_symbol {int type; int /*<<< orphan*/  symbol; } ;
typedef  enum perf_pmu_event_symbol_type { ____Placeholder_perf_pmu_event_symbol_type } perf_pmu_event_symbol_type ;

/* Variables and functions */
 int PMU_EVENT_SYMBOL_ERR ; 
 struct perf_pmu_event_symbol* bsearch (struct perf_pmu_event_symbol*,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comp_pmu ; 
 int /*<<< orphan*/  perf_pmu__parse_init () ; 
 int /*<<< orphan*/  perf_pmu_events_list ; 
 scalar_t__ perf_pmu_events_list_num ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

enum perf_pmu_event_symbol_type
perf_pmu__parse_check(const char *name)
{
	struct perf_pmu_event_symbol p, *r;

	/* scan kernel pmu events from sysfs if needed */
	if (perf_pmu_events_list_num == 0)
		perf_pmu__parse_init();
	/*
	 * name "cpu" could be prefix of cpu-cycles or cpu// events.
	 * cpu-cycles has been handled by hardcode.
	 * So it must be cpu// events, not kernel pmu event.
	 */
	if ((perf_pmu_events_list_num <= 0) || !strcmp(name, "cpu"))
		return PMU_EVENT_SYMBOL_ERR;

	p.symbol = strdup(name);
	r = bsearch(&p, perf_pmu_events_list,
			(size_t) perf_pmu_events_list_num,
			sizeof(struct perf_pmu_event_symbol), comp_pmu);
	zfree(&p.symbol);
	return r ? r->type : PMU_EVENT_SYMBOL_ERR;
}