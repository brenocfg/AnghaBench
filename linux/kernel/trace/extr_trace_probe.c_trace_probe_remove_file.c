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
struct trace_probe {TYPE_1__* event; } ;
struct trace_event_file {int dummy; } ;
struct event_file_link {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TP_FLAG_TRACE ; 
 int /*<<< orphan*/  kfree (struct event_file_link*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  trace_probe_clear_flag (struct trace_probe*,int /*<<< orphan*/ ) ; 
 struct event_file_link* trace_probe_get_file_link (struct trace_probe*,struct trace_event_file*) ; 

int trace_probe_remove_file(struct trace_probe *tp,
			    struct trace_event_file *file)
{
	struct event_file_link *link;

	link = trace_probe_get_file_link(tp, file);
	if (!link)
		return -ENOENT;

	list_del_rcu(&link->list);
	synchronize_rcu();
	kfree(link);

	if (list_empty(&tp->event->files))
		trace_probe_clear_flag(tp, TP_FLAG_TRACE);

	return 0;
}