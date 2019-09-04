#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct trace_uprobe* name; TYPE_1__* class; } ;
struct TYPE_5__ {void* system; } ;
struct TYPE_8__ {TYPE_3__ call; int /*<<< orphan*/  files; TYPE_1__ class; } ;
struct TYPE_6__ {int /*<<< orphan*/  ret_handler; int /*<<< orphan*/  handler; } ;
struct trace_uprobe {TYPE_4__ tp; int /*<<< orphan*/  filter; TYPE_2__ consumer; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct trace_uprobe* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIZEOF_TRACE_UPROBE (int) ; 
 int /*<<< orphan*/  init_trace_uprobe_filter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_good_name (char const*) ; 
 int /*<<< orphan*/  kfree (struct trace_uprobe*) ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct trace_uprobe* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprobe_dispatcher ; 
 int /*<<< orphan*/  uretprobe_dispatcher ; 

__attribute__((used)) static struct trace_uprobe *
alloc_trace_uprobe(const char *group, const char *event, int nargs, bool is_ret)
{
	struct trace_uprobe *tu;

	if (!event || !is_good_name(event))
		return ERR_PTR(-EINVAL);

	if (!group || !is_good_name(group))
		return ERR_PTR(-EINVAL);

	tu = kzalloc(SIZEOF_TRACE_UPROBE(nargs), GFP_KERNEL);
	if (!tu)
		return ERR_PTR(-ENOMEM);

	tu->tp.call.class = &tu->tp.class;
	tu->tp.call.name = kstrdup(event, GFP_KERNEL);
	if (!tu->tp.call.name)
		goto error;

	tu->tp.class.system = kstrdup(group, GFP_KERNEL);
	if (!tu->tp.class.system)
		goto error;

	INIT_LIST_HEAD(&tu->list);
	INIT_LIST_HEAD(&tu->tp.files);
	tu->consumer.handler = uprobe_dispatcher;
	if (is_ret)
		tu->consumer.ret_handler = uretprobe_dispatcher;
	init_trace_uprobe_filter(&tu->filter);
	return tu;

error:
	kfree(tu->tp.call.name);
	kfree(tu);

	return ERR_PTR(-ENOMEM);
}