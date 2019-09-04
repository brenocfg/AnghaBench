#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  files; } ;
struct trace_uprobe {TYPE_1__ tp; int /*<<< orphan*/ * inode; int /*<<< orphan*/  consumer; int /*<<< orphan*/  offset; int /*<<< orphan*/  filter; } ;
struct trace_event_file {int dummy; } ;
struct event_file_link {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_FLAG_PROFILE ; 
 int /*<<< orphan*/  TP_FLAG_TRACE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct event_file_link* find_event_file_link (TYPE_1__*,struct trace_event_file*) ; 
 int /*<<< orphan*/  kfree (struct event_file_link*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  trace_probe_is_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  uprobe_buffer_disable () ; 
 int /*<<< orphan*/  uprobe_filter_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprobe_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
probe_event_disable(struct trace_uprobe *tu, struct trace_event_file *file)
{
	if (!trace_probe_is_enabled(&tu->tp))
		return;

	if (file) {
		struct event_file_link *link;

		link = find_event_file_link(&tu->tp, file);
		if (!link)
			return;

		list_del_rcu(&link->list);
		/* synchronize with u{,ret}probe_trace_func */
		synchronize_rcu();
		kfree(link);

		if (!list_empty(&tu->tp.files))
			return;
	}

	WARN_ON(!uprobe_filter_is_empty(&tu->filter));

	uprobe_unregister(tu->inode, tu->offset, &tu->consumer);
	tu->inode = NULL;
	tu->tp.flags &= file ? ~TP_FLAG_TRACE : ~TP_FLAG_PROFILE;

	uprobe_buffer_disable();
}