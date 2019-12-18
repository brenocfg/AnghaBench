#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_uprobe {int /*<<< orphan*/  tp; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct trace_event_call {int flags; TYPE_2__* class; TYPE_1__ event; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  define_fields; } ;

/* Variables and functions */
 int TRACE_EVENT_FL_CAP_ANY ; 
 int TRACE_EVENT_FL_UPROBE ; 
 struct trace_event_call* trace_probe_event_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_uprobe_register ; 
 int /*<<< orphan*/  uprobe_event_define_fields ; 
 int /*<<< orphan*/  uprobe_funcs ; 

__attribute__((used)) static inline void init_trace_event_call(struct trace_uprobe *tu)
{
	struct trace_event_call *call = trace_probe_event_call(&tu->tp);

	call->event.funcs = &uprobe_funcs;
	call->class->define_fields = uprobe_event_define_fields;

	call->flags = TRACE_EVENT_FL_UPROBE | TRACE_EVENT_FL_CAP_ANY;
	call->class->reg = trace_uprobe_register;
}