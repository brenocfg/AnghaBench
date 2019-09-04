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
struct trace_kprobe {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * funcs; } ;
struct trace_event_call {struct trace_kprobe* data; TYPE_1__* class; int /*<<< orphan*/  flags; TYPE_2__ event; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  define_fields; int /*<<< orphan*/  fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_EVENT_FL_KPROBE ; 
 int /*<<< orphan*/  kprobe_event_define_fields ; 
 int /*<<< orphan*/  kprobe_funcs ; 
 int /*<<< orphan*/  kprobe_register ; 
 int /*<<< orphan*/  kretprobe_event_define_fields ; 
 int /*<<< orphan*/  kretprobe_funcs ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 

__attribute__((used)) static inline void init_trace_event_call(struct trace_kprobe *tk,
					 struct trace_event_call *call)
{
	INIT_LIST_HEAD(&call->class->fields);
	if (trace_kprobe_is_return(tk)) {
		call->event.funcs = &kretprobe_funcs;
		call->class->define_fields = kretprobe_event_define_fields;
	} else {
		call->event.funcs = &kprobe_funcs;
		call->class->define_fields = kprobe_event_define_fields;
	}

	call->flags = TRACE_EVENT_FL_KPROBE;
	call->class->reg = kprobe_register;
	call->data = tk;
}