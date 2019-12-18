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
struct trace_event_file {int flags; TYPE_1__* class; int /*<<< orphan*/  tp; } ;
struct trace_event_call {int flags; TYPE_1__* class; int /*<<< orphan*/  tp; } ;
typedef  enum trace_reg { ____Placeholder_trace_reg } trace_reg ;
struct TYPE_2__ {int /*<<< orphan*/  perf_probe; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int TRACE_EVENT_FL_TRACEPOINT ; 
#define  TRACE_REG_PERF_ADD 135 
#define  TRACE_REG_PERF_CLOSE 134 
#define  TRACE_REG_PERF_DEL 133 
#define  TRACE_REG_PERF_OPEN 132 
#define  TRACE_REG_PERF_REGISTER 131 
#define  TRACE_REG_PERF_UNREGISTER 130 
#define  TRACE_REG_REGISTER 129 
#define  TRACE_REG_UNREGISTER 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int tracepoint_probe_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct trace_event_file*) ; 
 int /*<<< orphan*/  tracepoint_probe_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct trace_event_file*) ; 

int trace_event_reg(struct trace_event_call *call,
		    enum trace_reg type, void *data)
{
	struct trace_event_file *file = data;

	WARN_ON(!(call->flags & TRACE_EVENT_FL_TRACEPOINT));
	switch (type) {
	case TRACE_REG_REGISTER:
		return tracepoint_probe_register(call->tp,
						 call->class->probe,
						 file);
	case TRACE_REG_UNREGISTER:
		tracepoint_probe_unregister(call->tp,
					    call->class->probe,
					    file);
		return 0;

#ifdef CONFIG_PERF_EVENTS
	case TRACE_REG_PERF_REGISTER:
		return tracepoint_probe_register(call->tp,
						 call->class->perf_probe,
						 call);
	case TRACE_REG_PERF_UNREGISTER:
		tracepoint_probe_unregister(call->tp,
					    call->class->perf_probe,
					    call);
		return 0;
	case TRACE_REG_PERF_OPEN:
	case TRACE_REG_PERF_CLOSE:
	case TRACE_REG_PERF_ADD:
	case TRACE_REG_PERF_DEL:
		return 0;
#endif
	}
	return 0;
}