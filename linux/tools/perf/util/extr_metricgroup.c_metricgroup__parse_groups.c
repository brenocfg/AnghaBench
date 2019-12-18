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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct rblist {scalar_t__ nr_entries; } ;
struct parse_events_error {int dummy; } ;
struct option {scalar_t__ value; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_list ; 
 int /*<<< orphan*/  memset (struct parse_events_error*,int /*<<< orphan*/ ,int) ; 
 int metricgroup__add_metric_list (char const*,struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metricgroup__free_egroups (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metricgroup__rblist_init (struct rblist*) ; 
 int metricgroup__setup_events (int /*<<< orphan*/ *,struct evlist*,struct rblist*) ; 
 int parse_events (struct evlist*,int /*<<< orphan*/ ,struct parse_events_error*) ; 
 int /*<<< orphan*/  parse_events_print_error (struct parse_events_error*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int metricgroup__parse_groups(const struct option *opt,
			   const char *str,
			   struct rblist *metric_events)
{
	struct parse_events_error parse_error;
	struct evlist *perf_evlist = *(struct evlist **)opt->value;
	struct strbuf extra_events;
	LIST_HEAD(group_list);
	int ret;

	if (metric_events->nr_entries == 0)
		metricgroup__rblist_init(metric_events);
	ret = metricgroup__add_metric_list(str, &extra_events, &group_list);
	if (ret)
		return ret;
	pr_debug("adding %s\n", extra_events.buf);
	memset(&parse_error, 0, sizeof(struct parse_events_error));
	ret = parse_events(perf_evlist, extra_events.buf, &parse_error);
	if (ret) {
		parse_events_print_error(&parse_error, extra_events.buf);
		goto out;
	}
	strbuf_release(&extra_events);
	ret = metricgroup__setup_events(&group_list, perf_evlist,
					metric_events);
out:
	metricgroup__free_egroups(&group_list);
	return ret;
}