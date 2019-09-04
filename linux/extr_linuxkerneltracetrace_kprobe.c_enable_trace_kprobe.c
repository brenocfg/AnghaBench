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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  files; } ;
struct trace_kprobe {TYPE_1__ tp; } ;
struct trace_event_file {int dummy; } ;
struct event_file_link {int /*<<< orphan*/  list; struct trace_event_file* file; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TP_FLAG_PROFILE ; 
 int /*<<< orphan*/  TP_FLAG_TRACE ; 
 int __enable_trace_kprobe (struct trace_kprobe*) ; 
 int /*<<< orphan*/  kfree (struct event_file_link*) ; 
 struct event_file_link* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
enable_trace_kprobe(struct trace_kprobe *tk, struct trace_event_file *file)
{
	struct event_file_link *link;
	int ret = 0;

	if (file) {
		link = kmalloc(sizeof(*link), GFP_KERNEL);
		if (!link) {
			ret = -ENOMEM;
			goto out;
		}

		link->file = file;
		list_add_tail_rcu(&link->list, &tk->tp.files);

		tk->tp.flags |= TP_FLAG_TRACE;
		ret = __enable_trace_kprobe(tk);
		if (ret) {
			list_del_rcu(&link->list);
			kfree(link);
			tk->tp.flags &= ~TP_FLAG_TRACE;
		}

	} else {
		tk->tp.flags |= TP_FLAG_PROFILE;
		ret = __enable_trace_kprobe(tk);
		if (ret)
			tk->tp.flags &= ~TP_FLAG_PROFILE;
	}
 out:
	return ret;
}