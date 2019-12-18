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
struct trace_event_file {int /*<<< orphan*/  tr; struct trace_event_call* event_call; } ;
struct trace_event_call {int dummy; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_filter (struct event_filter*) ; 
 int create_filter (int /*<<< orphan*/ ,struct trace_event_call*,char*,int,struct event_filter**) ; 
 int /*<<< orphan*/  event_clear_filter (struct trace_event_file*) ; 
 struct event_filter* event_filter (struct trace_event_file*) ; 
 int /*<<< orphan*/  event_set_filter (struct trace_event_file*,struct event_filter*) ; 
 int /*<<< orphan*/  event_set_filtered_flag (struct trace_event_file*) ; 
 int /*<<< orphan*/  filter_disable (struct trace_event_file*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstrip (char*) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 

int apply_event_filter(struct trace_event_file *file, char *filter_string)
{
	struct trace_event_call *call = file->event_call;
	struct event_filter *filter = NULL;
	int err;

	if (!strcmp(strstrip(filter_string), "0")) {
		filter_disable(file);
		filter = event_filter(file);

		if (!filter)
			return 0;

		event_clear_filter(file);

		/* Make sure the filter is not being used */
		tracepoint_synchronize_unregister();
		__free_filter(filter);

		return 0;
	}

	err = create_filter(file->tr, call, filter_string, true, &filter);

	/*
	 * Always swap the call filter with the new filter
	 * even if there was an error. If there was an error
	 * in the filter, we disable the filter and show the error
	 * string
	 */
	if (filter) {
		struct event_filter *tmp;

		tmp = event_filter(file);
		if (!err)
			event_set_filtered_flag(file);
		else
			filter_disable(file);

		event_set_filter(file, filter);

		if (tmp) {
			/* Make sure the call is done with the filter */
			tracepoint_synchronize_unregister();
			__free_filter(tmp);
		}
	}

	return err;
}