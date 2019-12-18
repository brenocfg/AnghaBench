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
struct trace_kprobe {int /*<<< orphan*/  tp; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct trace_event_call {TYPE_2__* class; int /*<<< orphan*/  flags; TYPE_1__ event; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  define_fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_EVENT_FL_KPROBE ; 
 int /*<<< orphan*/  kprobe_event_define_fields ; 
 int /*<<< orphan*/  kprobe_funcs ; 
 int /*<<< orphan*/  kprobe_register ; 
 int /*<<< orphan*/  kretprobe_event_define_fields ; 
 int /*<<< orphan*/  kretprobe_funcs ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 
 struct trace_event_call* trace_probe_event_call (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void init_trace_event_call(struct trace_kprobe *tk)
{
	struct trace_event_call *call = trace_probe_event_call(&tk->tp);

	if (trace_kprobe_is_return(tk)) {
		call->event.funcs = &kretprobe_funcs;
		call->class->define_fields = kretprobe_event_define_fields;
	} else {
		call->event.funcs = &kprobe_funcs;
		call->class->define_fields = kprobe_event_define_fields;
	}

	call->flags = TRACE_EVENT_FL_KPROBE;
	call->class->reg = kprobe_register;
}