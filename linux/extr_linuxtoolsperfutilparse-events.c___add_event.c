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
struct perf_pmu {int is_uncore; struct cpu_map* cpus; } ;
struct perf_evsel {int system_wide; int auto_merge_stats; int /*<<< orphan*/  node; int /*<<< orphan*/  config_terms; int /*<<< orphan*/  name; void* own_cpus; void* cpus; } ;
struct perf_event_attr {int dummy; } ;
struct list_head {int dummy; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 void* cpu_map__get (struct cpu_map*) ; 
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,int /*<<< orphan*/ *) ; 
 struct perf_evsel* perf_evsel__new_idx (struct perf_event_attr*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static struct perf_evsel *
__add_event(struct list_head *list, int *idx,
	    struct perf_event_attr *attr,
	    char *name, struct perf_pmu *pmu,
	    struct list_head *config_terms, bool auto_merge_stats)
{
	struct perf_evsel *evsel;
	struct cpu_map *cpus = pmu ? pmu->cpus : NULL;

	event_attr_init(attr);

	evsel = perf_evsel__new_idx(attr, *idx);
	if (!evsel)
		return NULL;

	(*idx)++;
	evsel->cpus        = cpu_map__get(cpus);
	evsel->own_cpus    = cpu_map__get(cpus);
	evsel->system_wide = pmu ? pmu->is_uncore : false;
	evsel->auto_merge_stats = auto_merge_stats;

	if (name)
		evsel->name = strdup(name);

	if (config_terms)
		list_splice(config_terms, &evsel->config_terms);

	list_add_tail(&evsel->node, list);
	return evsel;
}