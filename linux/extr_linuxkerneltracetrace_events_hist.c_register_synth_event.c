#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * funcs; } ;
struct trace_event_call {TYPE_2__ event; int /*<<< orphan*/ * tp; struct synth_event* data; TYPE_1__* class; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  probe; int /*<<< orphan*/  reg; int /*<<< orphan*/  define_fields; int /*<<< orphan*/  fields; int /*<<< orphan*/  system; } ;
struct synth_event {int /*<<< orphan*/ * tp; int /*<<< orphan*/  name; TYPE_1__ class; struct trace_event_call call; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYNTH_SYSTEM ; 
 int /*<<< orphan*/  TRACE_EVENT_FL_TRACEPOINT ; 
 int /*<<< orphan*/ * alloc_synth_tracepoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int register_trace_event (TYPE_2__*) ; 
 int set_synth_event_print_fmt (struct trace_event_call*) ; 
 int /*<<< orphan*/  synth_event_define_fields ; 
 int /*<<< orphan*/  synth_event_funcs ; 
 int trace_add_event_call (struct trace_event_call*) ; 
 int /*<<< orphan*/  trace_event_name (struct trace_event_call*) ; 
 int /*<<< orphan*/  trace_event_raw_event_synth ; 
 int /*<<< orphan*/  trace_event_reg ; 
 int /*<<< orphan*/  trace_remove_event_call (struct trace_event_call*) ; 
 int /*<<< orphan*/  unregister_trace_event (TYPE_2__*) ; 

__attribute__((used)) static int register_synth_event(struct synth_event *event)
{
	struct trace_event_call *call = &event->call;
	int ret = 0;

	event->call.class = &event->class;
	event->class.system = kstrdup(SYNTH_SYSTEM, GFP_KERNEL);
	if (!event->class.system) {
		ret = -ENOMEM;
		goto out;
	}

	event->tp = alloc_synth_tracepoint(event->name);
	if (IS_ERR(event->tp)) {
		ret = PTR_ERR(event->tp);
		event->tp = NULL;
		goto out;
	}

	INIT_LIST_HEAD(&call->class->fields);
	call->event.funcs = &synth_event_funcs;
	call->class->define_fields = synth_event_define_fields;

	ret = register_trace_event(&call->event);
	if (!ret) {
		ret = -ENODEV;
		goto out;
	}
	call->flags = TRACE_EVENT_FL_TRACEPOINT;
	call->class->reg = trace_event_reg;
	call->class->probe = trace_event_raw_event_synth;
	call->data = event;
	call->tp = event->tp;

	ret = trace_add_event_call(call);
	if (ret) {
		pr_warn("Failed to register synthetic event: %s\n",
			trace_event_name(call));
		goto err;
	}

	ret = set_synth_event_print_fmt(call);
	if (ret < 0) {
		trace_remove_event_call(call);
		goto err;
	}
 out:
	return ret;
 err:
	unregister_trace_event(&call->event);
	goto out;
}