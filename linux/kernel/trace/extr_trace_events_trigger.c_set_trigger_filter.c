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
struct trace_event_file {int /*<<< orphan*/  event_call; int /*<<< orphan*/  tr; } ;
struct event_trigger_data {int /*<<< orphan*/ * filter; int /*<<< orphan*/ * filter_str; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int create_event_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct event_filter**) ; 
 int /*<<< orphan*/  free_event_filter (struct event_filter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct event_filter* rcu_access_pointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct event_filter*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 

int set_trigger_filter(char *filter_str,
		       struct event_trigger_data *trigger_data,
		       struct trace_event_file *file)
{
	struct event_trigger_data *data = trigger_data;
	struct event_filter *filter = NULL, *tmp;
	int ret = -EINVAL;
	char *s;

	if (!filter_str) /* clear the current filter */
		goto assign;

	s = strsep(&filter_str, " \t");

	if (!strlen(s) || strcmp(s, "if") != 0)
		goto out;

	if (!filter_str)
		goto out;

	/* The filter is for the 'trigger' event, not the triggered event */
	ret = create_event_filter(file->tr, file->event_call,
				  filter_str, false, &filter);
	/*
	 * If create_event_filter() fails, filter still needs to be freed.
	 * Which the calling code will do with data->filter.
	 */
 assign:
	tmp = rcu_access_pointer(data->filter);

	rcu_assign_pointer(data->filter, filter);

	if (tmp) {
		/* Make sure the call is done with the filter */
		tracepoint_synchronize_unregister();
		free_event_filter(tmp);
	}

	kfree(data->filter_str);
	data->filter_str = NULL;

	if (filter_str) {
		data->filter_str = kstrdup(filter_str, GFP_KERNEL);
		if (!data->filter_str) {
			free_event_filter(rcu_access_pointer(data->filter));
			data->filter = NULL;
			ret = -ENOMEM;
		}
	}
 out:
	return ret;
}