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
struct perf_session {int /*<<< orphan*/  evlist; } ;
struct evsel_str_handler {int /*<<< orphan*/ * handler; int /*<<< orphan*/  name; } ;
struct evsel {int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int EEXIST ; 
 struct evsel* perf_evlist__find_tracepoint_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __perf_session__set_tracepoints_handlers(struct perf_session *session,
					     const struct evsel_str_handler *assocs,
					     size_t nr_assocs)
{
	struct evsel *evsel;
	size_t i;
	int err;

	for (i = 0; i < nr_assocs; i++) {
		/*
		 * Adding a handler for an event not in the session,
		 * just ignore it.
		 */
		evsel = perf_evlist__find_tracepoint_by_name(session->evlist, assocs[i].name);
		if (evsel == NULL)
			continue;

		err = -EEXIST;
		if (evsel->handler != NULL)
			goto out;
		evsel->handler = assocs[i].handler;
	}

	err = 0;
out:
	return err;
}