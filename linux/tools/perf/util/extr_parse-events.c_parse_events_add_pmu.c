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
struct perf_pmu_info {int /*<<< orphan*/  metric_name; int /*<<< orphan*/  metric_expr; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  per_pkg; int /*<<< orphan*/  scale; int /*<<< orphan*/  unit; } ;
struct perf_pmu {int /*<<< orphan*/  type; scalar_t__ is_uncore; scalar_t__ default_config; } ;
struct perf_event_attr {int /*<<< orphan*/  type; } ;
struct parse_events_state {int /*<<< orphan*/  idx; struct parse_events_error* error; } ;
struct parse_events_error {int /*<<< orphan*/ * str; } ;
struct list_head {int dummy; } ;
struct evsel {char* pmu_name; int use_uncore_alias; int /*<<< orphan*/  config_terms; int /*<<< orphan*/  percore; int /*<<< orphan*/  metric_name; int /*<<< orphan*/  metric_expr; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  per_pkg; int /*<<< orphan*/  scale; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct evsel* __add_event (struct list_head*,int /*<<< orphan*/ *,struct perf_event_attr*,int /*<<< orphan*/ *,struct perf_pmu*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,char*) ; 
 scalar_t__ config_attr (struct perf_event_attr*,struct list_head*,struct parse_events_error*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_term_percore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_term_pmu ; 
 int /*<<< orphan*/  config_terms ; 
 int /*<<< orphan*/ * get_config_name (struct list_head*) ; 
 scalar_t__ get_config_terms (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct perf_event_attr*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ perf_pmu__check_alias (struct perf_pmu*,struct list_head*,struct perf_pmu_info*) ; 
 scalar_t__ perf_pmu__config (struct perf_pmu*,struct perf_event_attr*,struct list_head*,struct parse_events_error*) ; 
 struct perf_pmu* perf_pmu__find (char*) ; 

int parse_events_add_pmu(struct parse_events_state *parse_state,
			 struct list_head *list, char *name,
			 struct list_head *head_config,
			 bool auto_merge_stats,
			 bool use_alias)
{
	struct perf_event_attr attr;
	struct perf_pmu_info info;
	struct perf_pmu *pmu;
	struct evsel *evsel;
	struct parse_events_error *err = parse_state->error;
	bool use_uncore_alias;
	LIST_HEAD(config_terms);

	pmu = perf_pmu__find(name);
	if (!pmu) {
		if (asprintf(&err->str,
				"Cannot find PMU `%s'. Missing kernel support?",
				name) < 0)
			err->str = NULL;
		return -EINVAL;
	}

	if (pmu->default_config) {
		memcpy(&attr, pmu->default_config,
		       sizeof(struct perf_event_attr));
	} else {
		memset(&attr, 0, sizeof(attr));
	}

	use_uncore_alias = (pmu->is_uncore && use_alias);

	if (!head_config) {
		attr.type = pmu->type;
		evsel = __add_event(list, &parse_state->idx, &attr, NULL, pmu, NULL,
				    auto_merge_stats, NULL);
		if (evsel) {
			evsel->pmu_name = name;
			evsel->use_uncore_alias = use_uncore_alias;
			return 0;
		} else {
			return -ENOMEM;
		}
	}

	if (perf_pmu__check_alias(pmu, head_config, &info))
		return -EINVAL;

	/*
	 * Configure hardcoded terms first, no need to check
	 * return value when called with fail == 0 ;)
	 */
	if (config_attr(&attr, head_config, parse_state->error, config_term_pmu))
		return -EINVAL;

	if (get_config_terms(head_config, &config_terms))
		return -ENOMEM;

	if (perf_pmu__config(pmu, &attr, head_config, parse_state->error))
		return -EINVAL;

	evsel = __add_event(list, &parse_state->idx, &attr,
			    get_config_name(head_config), pmu,
			    &config_terms, auto_merge_stats, NULL);
	if (evsel) {
		evsel->unit = info.unit;
		evsel->scale = info.scale;
		evsel->per_pkg = info.per_pkg;
		evsel->snapshot = info.snapshot;
		evsel->metric_expr = info.metric_expr;
		evsel->metric_name = info.metric_name;
		evsel->pmu_name = name;
		evsel->use_uncore_alias = use_uncore_alias;
		evsel->percore = config_term_percore(&evsel->config_terms);
	}

	return evsel ? 0 : -ENOMEM;
}