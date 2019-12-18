#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_pmu {int is_uncore; struct perf_cpu_map* cpus; } ;
struct perf_event_attr {int dummy; } ;
struct perf_cpu_map {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int system_wide; int /*<<< orphan*/  node; void* own_cpus; void* cpus; } ;
struct evsel {int auto_merge_stats; TYPE_1__ core; int /*<<< orphan*/  config_terms; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_attr_init (struct perf_event_attr*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_splice (struct list_head*,int /*<<< orphan*/ *) ; 
 void* perf_cpu_map__get (struct perf_cpu_map*) ; 
 struct perf_cpu_map* perf_cpu_map__new (char const*) ; 
 struct evsel* perf_evsel__new_idx (struct perf_event_attr*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static struct evsel *
__add_event(struct list_head *list, int *idx,
	    struct perf_event_attr *attr,
	    char *name, struct perf_pmu *pmu,
	    struct list_head *config_terms, bool auto_merge_stats,
	    const char *cpu_list)
{
	struct evsel *evsel;
	struct perf_cpu_map *cpus = pmu ? pmu->cpus :
			       cpu_list ? perf_cpu_map__new(cpu_list) : NULL;

	event_attr_init(attr);

	evsel = perf_evsel__new_idx(attr, *idx);
	if (!evsel)
		return NULL;

	(*idx)++;
	evsel->core.cpus   = perf_cpu_map__get(cpus);
	evsel->core.own_cpus = perf_cpu_map__get(cpus);
	evsel->core.system_wide = pmu ? pmu->is_uncore : false;
	evsel->auto_merge_stats = auto_merge_stats;

	if (name)
		evsel->name = strdup(name);

	if (config_terms)
		list_splice(config_terms, &evsel->config_terms);

	list_add_tail(&evsel->core.node, list);
	return evsel;
}