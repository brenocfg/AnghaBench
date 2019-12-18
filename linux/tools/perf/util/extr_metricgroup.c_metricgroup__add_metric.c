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
struct strbuf {scalar_t__ len; } ;
struct pmu_events_map {struct pmu_event* table; } ;
struct pmu_event {int /*<<< orphan*/  unit; scalar_t__ metric_expr; scalar_t__ metric_name; scalar_t__ metric_group; int /*<<< orphan*/  name; } ;
struct list_head {int dummy; } ;
struct egroup {char const** ids; int idnum; int /*<<< orphan*/  nd; int /*<<< orphan*/  metric_unit; scalar_t__ metric_expr; scalar_t__ metric_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ expr__find_other (scalar_t__,int /*<<< orphan*/ *,char const***,int*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct egroup* malloc (int) ; 
 scalar_t__ match_metric (scalar_t__,char const*) ; 
 struct pmu_events_map* perf_pmu__find_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int metricgroup__add_metric(const char *metric, struct strbuf *events,
				   struct list_head *group_list)
{
	struct pmu_events_map *map = perf_pmu__find_map(NULL);
	struct pmu_event *pe;
	int ret = -EINVAL;
	int i, j;

	if (!map)
		return 0;

	for (i = 0; ; i++) {
		pe = &map->table[i];

		if (!pe->name && !pe->metric_group && !pe->metric_name)
			break;
		if (!pe->metric_expr)
			continue;
		if (match_metric(pe->metric_group, metric) ||
		    match_metric(pe->metric_name, metric)) {
			const char **ids;
			int idnum;
			struct egroup *eg;
			bool no_group = false;

			pr_debug("metric expr %s for %s\n", pe->metric_expr, pe->metric_name);

			if (expr__find_other(pe->metric_expr,
					     NULL, &ids, &idnum) < 0)
				continue;
			if (events->len > 0)
				strbuf_addf(events, ",");
			for (j = 0; j < idnum; j++) {
				pr_debug("found event %s\n", ids[j]);
				/*
				 * Duration time maps to a software event and can make
				 * groups not count. Always use it outside a
				 * group.
				 */
				if (!strcmp(ids[j], "duration_time")) {
					if (j > 0)
						strbuf_addf(events, "}:W,");
					strbuf_addf(events, "duration_time");
					no_group = true;
					continue;
				}
				strbuf_addf(events, "%s%s",
					j == 0 || no_group ? "{" : ",",
					ids[j]);
				no_group = false;
			}
			if (!no_group)
				strbuf_addf(events, "}:W");

			eg = malloc(sizeof(struct egroup));
			if (!eg) {
				ret = -ENOMEM;
				break;
			}
			eg->ids = ids;
			eg->idnum = idnum;
			eg->metric_name = pe->metric_name;
			eg->metric_expr = pe->metric_expr;
			eg->metric_unit = pe->unit;
			list_add_tail(&eg->nd, group_list);
			ret = 0;
		}
	}
	return ret;
}