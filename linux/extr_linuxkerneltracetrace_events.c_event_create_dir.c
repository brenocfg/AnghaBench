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
struct trace_event_file {int flags; int /*<<< orphan*/  dir; TYPE_1__* class; struct trace_array* tr; struct trace_event_file* event_call; } ;
struct trace_event_call {int flags; int /*<<< orphan*/  dir; TYPE_1__* class; struct trace_array* tr; struct trace_event_call* event_call; } ;
struct trace_array {int dummy; } ;
struct list_head {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* define_fields ) (struct trace_event_file*) ;scalar_t__ reg; int /*<<< orphan*/  system; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TRACE_EVENT_FL_IGNORE_ENABLE ; 
 int /*<<< orphan*/  TRACE_SYSTEM ; 
 struct dentry* event_subsystem_dir (struct trace_array*,int /*<<< orphan*/ ,struct trace_event_file*,struct dentry*) ; 
 int /*<<< orphan*/  event_trigger_fops ; 
 int /*<<< orphan*/  ftrace_enable_fops ; 
 int /*<<< orphan*/  ftrace_event_filter_fops ; 
 int /*<<< orphan*/  ftrace_event_format_fops ; 
 scalar_t__ list_empty (struct list_head*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct trace_event_file*) ; 
 int /*<<< orphan*/  trace_create_file (char*,int,int /*<<< orphan*/ ,struct trace_event_file*,int /*<<< orphan*/ *) ; 
 char* trace_event_name (struct trace_event_file*) ; 
 struct list_head* trace_get_fields (struct trace_event_file*) ; 
 int /*<<< orphan*/  tracefs_create_dir (char const*,struct dentry*) ; 

__attribute__((used)) static int
event_create_dir(struct dentry *parent, struct trace_event_file *file)
{
	struct trace_event_call *call = file->event_call;
	struct trace_array *tr = file->tr;
	struct list_head *head;
	struct dentry *d_events;
	const char *name;
	int ret;

	/*
	 * If the trace point header did not define TRACE_SYSTEM
	 * then the system would be called "TRACE_SYSTEM".
	 */
	if (strcmp(call->class->system, TRACE_SYSTEM) != 0) {
		d_events = event_subsystem_dir(tr, call->class->system, file, parent);
		if (!d_events)
			return -ENOMEM;
	} else
		d_events = parent;

	name = trace_event_name(call);
	file->dir = tracefs_create_dir(name, d_events);
	if (!file->dir) {
		pr_warn("Could not create tracefs '%s' directory\n", name);
		return -1;
	}

	if (call->class->reg && !(call->flags & TRACE_EVENT_FL_IGNORE_ENABLE))
		trace_create_file("enable", 0644, file->dir, file,
				  &ftrace_enable_fops);

#ifdef CONFIG_PERF_EVENTS
	if (call->event.type && call->class->reg)
		trace_create_file("id", 0444, file->dir,
				  (void *)(long)call->event.type,
				  &ftrace_event_id_fops);
#endif

	/*
	 * Other events may have the same class. Only update
	 * the fields if they are not already defined.
	 */
	head = trace_get_fields(call);
	if (list_empty(head)) {
		ret = call->class->define_fields(call);
		if (ret < 0) {
			pr_warn("Could not initialize trace point events/%s\n",
				name);
			return -1;
		}
	}

	/*
	 * Only event directories that can be enabled should have
	 * triggers or filters.
	 */
	if (!(call->flags & TRACE_EVENT_FL_IGNORE_ENABLE)) {
		trace_create_file("filter", 0644, file->dir, file,
				  &ftrace_event_filter_fops);

		trace_create_file("trigger", 0644, file->dir, file,
				  &event_trigger_fops);
	}

#ifdef CONFIG_HIST_TRIGGERS
	trace_create_file("hist", 0444, file->dir, file,
			  &event_hist_fops);
#endif
	trace_create_file("format", 0444, file->dir, call,
			  &ftrace_event_format_fops);

	return 0;
}