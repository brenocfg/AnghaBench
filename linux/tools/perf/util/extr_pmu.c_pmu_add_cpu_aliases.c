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
struct pmu_events_map {struct pmu_event* table; } ;
struct pmu_event {char const* pmu; scalar_t__ metric_name; scalar_t__ metric_expr; scalar_t__ perpkg; scalar_t__ unit; scalar_t__ topic; scalar_t__ long_desc; scalar_t__ event; scalar_t__ desc; scalar_t__ name; scalar_t__ metric_group; } ;
struct perf_pmu {char* name; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_pmu__new_alias (struct list_head*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ is_arm_pmu_core (char const*) ; 
 struct pmu_events_map* perf_pmu__find_map (struct perf_pmu*) ; 
 scalar_t__ pmu_is_uncore (char const*) ; 
 scalar_t__ pmu_uncore_alias_match (char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void pmu_add_cpu_aliases(struct list_head *head, struct perf_pmu *pmu)
{
	int i;
	struct pmu_events_map *map;
	const char *name = pmu->name;

	map = perf_pmu__find_map(pmu);
	if (!map)
		return;

	/*
	 * Found a matching PMU events table. Create aliases
	 */
	i = 0;
	while (1) {
		const char *cpu_name = is_arm_pmu_core(name) ? name : "cpu";
		struct pmu_event *pe = &map->table[i++];
		const char *pname = pe->pmu ? pe->pmu : cpu_name;

		if (!pe->name) {
			if (pe->metric_group || pe->metric_name)
				continue;
			break;
		}

		if (pmu_is_uncore(name) &&
		    pmu_uncore_alias_match(pname, name))
			goto new_alias;

		if (strcmp(pname, name))
			continue;

new_alias:
		/* need type casts to override 'const' */
		__perf_pmu__new_alias(head, NULL, (char *)pe->name,
				(char *)pe->desc, (char *)pe->event,
				(char *)pe->long_desc, (char *)pe->topic,
				(char *)pe->unit, (char *)pe->perpkg,
				(char *)pe->metric_expr,
				(char *)pe->metric_name);
	}
}