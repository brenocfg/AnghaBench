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
struct parse_events_state {scalar_t__ nr_groups; int /*<<< orphan*/  list; struct evlist* evlist; struct parse_events_error* error; int /*<<< orphan*/  idx; } ;
struct parse_events_error {int dummy; } ;
struct evsel {int cmdline_group_boundary; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;
struct evlist {int /*<<< orphan*/  nr_groups; TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PE_START_EVENTS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct evsel* evlist__last (struct evlist*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int parse_events__scanner (char const*,struct parse_events_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evlist__splice_list_tail (struct evlist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_pmu__parse_cleanup () ; 

int parse_events(struct evlist *evlist, const char *str,
		 struct parse_events_error *err)
{
	struct parse_events_state parse_state = {
		.list   = LIST_HEAD_INIT(parse_state.list),
		.idx    = evlist->core.nr_entries,
		.error  = err,
		.evlist = evlist,
	};
	int ret;

	ret = parse_events__scanner(str, &parse_state, PE_START_EVENTS);
	perf_pmu__parse_cleanup();
	if (!ret) {
		struct evsel *last;

		if (list_empty(&parse_state.list)) {
			WARN_ONCE(true, "WARNING: event parser found nothing\n");
			return -1;
		}

		perf_evlist__splice_list_tail(evlist, &parse_state.list);
		evlist->nr_groups += parse_state.nr_groups;
		last = evlist__last(evlist);
		last->cmdline_group_boundary = true;

		return 0;
	}

	/*
	 * There are 2 users - builtin-record and builtin-test objects.
	 * Both call evlist__delete in case of error, so we dont
	 * need to bother.
	 */
	return ret;
}