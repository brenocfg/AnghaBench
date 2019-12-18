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
struct TYPE_2__ {int /*<<< orphan*/  ret_handler; int /*<<< orphan*/  handler; } ;
struct trace_uprobe {int /*<<< orphan*/  filter; TYPE_1__ consumer; int /*<<< orphan*/  devent; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct trace_uprobe* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIZEOF_TRACE_UPROBE (int) ; 
 int /*<<< orphan*/  dyn_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_trace_uprobe_filter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct trace_uprobe*) ; 
 struct trace_uprobe* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trace_probe_init (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  trace_uprobe_ops ; 
 int /*<<< orphan*/  uprobe_dispatcher ; 
 int /*<<< orphan*/  uretprobe_dispatcher ; 

__attribute__((used)) static struct trace_uprobe *
alloc_trace_uprobe(const char *group, const char *event, int nargs, bool is_ret)
{
	struct trace_uprobe *tu;
	int ret;

	tu = kzalloc(SIZEOF_TRACE_UPROBE(nargs), GFP_KERNEL);
	if (!tu)
		return ERR_PTR(-ENOMEM);

	ret = trace_probe_init(&tu->tp, event, group);
	if (ret < 0)
		goto error;

	dyn_event_init(&tu->devent, &trace_uprobe_ops);
	tu->consumer.handler = uprobe_dispatcher;
	if (is_ret)
		tu->consumer.ret_handler = uretprobe_dispatcher;
	init_trace_uprobe_filter(&tu->filter);
	return tu;

error:
	kfree(tu);

	return ERR_PTR(ret);
}