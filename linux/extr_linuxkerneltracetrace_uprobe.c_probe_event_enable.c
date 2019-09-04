#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  files; } ;
struct TYPE_5__ {int /*<<< orphan*/  filter; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry; } ;
struct trace_uprobe {TYPE_3__ tp; TYPE_2__ consumer; int /*<<< orphan*/  offset; int /*<<< orphan*/  inode; TYPE_1__ path; int /*<<< orphan*/  filter; } ;
struct trace_event_file {int dummy; } ;
struct event_file_link {int /*<<< orphan*/  list; struct trace_event_file* file; } ;
typedef  int /*<<< orphan*/  filter_func_t ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TP_FLAG_PROFILE ; 
 int TP_FLAG_TRACE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  d_real_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct event_file_link*) ; 
 struct event_file_link* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int trace_probe_is_enabled (TYPE_3__*) ; 
 int /*<<< orphan*/  uprobe_buffer_disable () ; 
 int uprobe_buffer_enable () ; 
 int /*<<< orphan*/  uprobe_filter_is_empty (int /*<<< orphan*/ *) ; 
 int uprobe_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
probe_event_enable(struct trace_uprobe *tu, struct trace_event_file *file,
		   filter_func_t filter)
{
	bool enabled = trace_probe_is_enabled(&tu->tp);
	struct event_file_link *link = NULL;
	int ret;

	if (file) {
		if (tu->tp.flags & TP_FLAG_PROFILE)
			return -EINTR;

		link = kmalloc(sizeof(*link), GFP_KERNEL);
		if (!link)
			return -ENOMEM;

		link->file = file;
		list_add_tail_rcu(&link->list, &tu->tp.files);

		tu->tp.flags |= TP_FLAG_TRACE;
	} else {
		if (tu->tp.flags & TP_FLAG_TRACE)
			return -EINTR;

		tu->tp.flags |= TP_FLAG_PROFILE;
	}

	WARN_ON(!uprobe_filter_is_empty(&tu->filter));

	if (enabled)
		return 0;

	ret = uprobe_buffer_enable();
	if (ret)
		goto err_flags;

	tu->consumer.filter = filter;
	tu->inode = d_real_inode(tu->path.dentry);
	ret = uprobe_register(tu->inode, tu->offset, &tu->consumer);
	if (ret)
		goto err_buffer;

	return 0;

 err_buffer:
	uprobe_buffer_disable();

 err_flags:
	if (file) {
		list_del(&link->list);
		kfree(link);
		tu->tp.flags &= ~TP_FLAG_TRACE;
	} else {
		tu->tp.flags &= ~TP_FLAG_PROFILE;
	}
	return ret;
}