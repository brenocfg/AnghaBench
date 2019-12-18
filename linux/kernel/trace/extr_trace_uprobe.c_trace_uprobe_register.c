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
#define  TRACE_REG_PERF_CLOSE 133 
#define  TRACE_REG_PERF_OPEN 132 
#define  TRACE_REG_PERF_REGISTER 131 
#define  TRACE_REG_PERF_UNREGISTER 130 
#define  TRACE_REG_REGISTER 129 
#define  TRACE_REG_UNREGISTER 128 
 int /*<<< orphan*/  probe_event_disable (struct trace_event_call*,struct trace_event_file*) ; 
 int probe_event_enable (struct trace_event_call*,struct trace_event_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprobe_perf_close ; 
 int /*<<< orphan*/ * uprobe_perf_filter ; 
 int uprobe_perf_multi_call (struct trace_event_call*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprobe_perf_open ; 

__attribute__((used)) static int
trace_uprobe_register(struct trace_event_call *event, enum trace_reg type,
		      void *data)
{
	struct trace_event_file *file = data;

	switch (type) {
	case TRACE_REG_REGISTER:
		return probe_event_enable(event, file, NULL);

	case TRACE_REG_UNREGISTER:
		probe_event_disable(event, file);
		return 0;

#ifdef CONFIG_PERF_EVENTS
	case TRACE_REG_PERF_REGISTER:
		return probe_event_enable(event, NULL, uprobe_perf_filter);

	case TRACE_REG_PERF_UNREGISTER:
		probe_event_disable(event, NULL);
		return 0;

	case TRACE_REG_PERF_OPEN:
		return uprobe_perf_multi_call(event, data, uprobe_perf_open);

	case TRACE_REG_PERF_CLOSE:
		return uprobe_perf_multi_call(event, data, uprobe_perf_close);

#endif
	default:
		return 0;
	}
	return 0;
}