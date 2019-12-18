#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct trace_event_file {int dummy; } ;
struct trace_event_call {int dummy; } ;
typedef  enum trace_reg { ____Placeholder_trace_reg } trace_reg ;

/* Variables and functions */
#define  TRACE_REG_PERF_ADD 135 
#define  TRACE_REG_PERF_CLOSE 134 
#define  TRACE_REG_PERF_DEL 133 
#define  TRACE_REG_PERF_OPEN 132 
#define  TRACE_REG_PERF_REGISTER 131 
#define  TRACE_REG_PERF_UNREGISTER 130 
#define  TRACE_REG_REGISTER 129 
#define  TRACE_REG_UNREGISTER 128 
 int disable_trace_kprobe (struct trace_event_call*,struct trace_event_file*) ; 
 int enable_trace_kprobe (struct trace_event_call*,struct trace_event_file*) ; 

__attribute__((used)) static int kprobe_register(struct trace_event_call *event,
			   enum trace_reg type, void *data)
{
	struct trace_event_file *file = data;

	switch (type) {
	case TRACE_REG_REGISTER:
		return enable_trace_kprobe(event, file);
	case TRACE_REG_UNREGISTER:
		return disable_trace_kprobe(event, file);

#ifdef CONFIG_PERF_EVENTS
	case TRACE_REG_PERF_REGISTER:
		return enable_trace_kprobe(event, NULL);
	case TRACE_REG_PERF_UNREGISTER:
		return disable_trace_kprobe(event, NULL);
	case TRACE_REG_PERF_OPEN:
	case TRACE_REG_PERF_CLOSE:
	case TRACE_REG_PERF_ADD:
	case TRACE_REG_PERF_DEL:
		return 0;
#endif
	}
	return 0;
}