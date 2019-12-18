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
struct trace_subsystem_dir {int /*<<< orphan*/  nr_events; struct trace_array* tr; struct event_subsystem* subsystem; } ;
struct trace_array {int dummy; } ;
struct event_subsystem {struct event_filter* filter; } ;
struct event_filter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  __free_filter (struct event_filter*) ; 
 int create_system_filter (struct trace_subsystem_dir*,struct trace_array*,char*,struct event_filter**) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  filter_free_subsystem_filters (struct trace_subsystem_dir*,struct trace_array*) ; 
 int /*<<< orphan*/  filter_free_subsystem_preds (struct trace_subsystem_dir*,struct trace_array*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_filter_string (struct event_filter*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstrip (char*) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 

int apply_subsystem_event_filter(struct trace_subsystem_dir *dir,
				 char *filter_string)
{
	struct event_subsystem *system = dir->subsystem;
	struct trace_array *tr = dir->tr;
	struct event_filter *filter = NULL;
	int err = 0;

	mutex_lock(&event_mutex);

	/* Make sure the system still has events */
	if (!dir->nr_events) {
		err = -ENODEV;
		goto out_unlock;
	}

	if (!strcmp(strstrip(filter_string), "0")) {
		filter_free_subsystem_preds(dir, tr);
		remove_filter_string(system->filter);
		filter = system->filter;
		system->filter = NULL;
		/* Ensure all filters are no longer used */
		tracepoint_synchronize_unregister();
		filter_free_subsystem_filters(dir, tr);
		__free_filter(filter);
		goto out_unlock;
	}

	err = create_system_filter(dir, tr, filter_string, &filter);
	if (filter) {
		/*
		 * No event actually uses the system filter
		 * we can free it without synchronize_rcu().
		 */
		__free_filter(system->filter);
		system->filter = filter;
	}
out_unlock:
	mutex_unlock(&event_mutex);

	return err;
}