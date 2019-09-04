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
struct trace_uprobe {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct trace_event_call {struct trace_uprobe* data; TYPE_2__* class; int /*<<< orphan*/  flags; TYPE_1__ event; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  define_fields; int /*<<< orphan*/  fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_EVENT_FL_UPROBE ; 
 int /*<<< orphan*/  trace_uprobe_register ; 
 int /*<<< orphan*/  uprobe_event_define_fields ; 
 int /*<<< orphan*/  uprobe_funcs ; 

__attribute__((used)) static inline void init_trace_event_call(struct trace_uprobe *tu,
					 struct trace_event_call *call)
{
	INIT_LIST_HEAD(&call->class->fields);
	call->event.funcs = &uprobe_funcs;
	call->class->define_fields = uprobe_event_define_fields;

	call->flags = TRACE_EVENT_FL_UPROBE;
	call->class->reg = trace_uprobe_register;
	call->data = tu;
}