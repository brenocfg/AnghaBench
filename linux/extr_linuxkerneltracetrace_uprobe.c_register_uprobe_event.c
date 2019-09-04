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
struct trace_event_call {int /*<<< orphan*/  event; int /*<<< orphan*/  print_fmt; } ;
struct TYPE_2__ {struct trace_event_call call; } ;
struct trace_uprobe {TYPE_1__ tp; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  init_trace_event_call (struct trace_uprobe*,struct trace_event_call*) ; 
 int /*<<< orphan*/  is_ret_probe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int register_trace_event (int /*<<< orphan*/ *) ; 
 scalar_t__ set_print_fmt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int trace_add_event_call (struct trace_event_call*) ; 
 int /*<<< orphan*/  trace_event_name (struct trace_event_call*) ; 
 int /*<<< orphan*/  unregister_trace_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_uprobe_event(struct trace_uprobe *tu)
{
	struct trace_event_call *call = &tu->tp.call;
	int ret = 0;

	init_trace_event_call(tu, call);

	if (set_print_fmt(&tu->tp, is_ret_probe(tu)) < 0)
		return -ENOMEM;

	ret = register_trace_event(&call->event);
	if (!ret) {
		kfree(call->print_fmt);
		return -ENODEV;
	}

	ret = trace_add_event_call(call);

	if (ret) {
		pr_info("Failed to register uprobe event: %s\n",
			trace_event_name(call));
		kfree(call->print_fmt);
		unregister_trace_event(&call->event);
	}

	return ret;
}