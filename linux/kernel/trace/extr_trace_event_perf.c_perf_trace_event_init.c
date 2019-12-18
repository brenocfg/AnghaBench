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
struct trace_event_call {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int perf_trace_event_open (struct perf_event*) ; 
 int perf_trace_event_perm (struct trace_event_call*,struct perf_event*) ; 
 int perf_trace_event_reg (struct trace_event_call*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_trace_event_unreg (struct perf_event*) ; 

__attribute__((used)) static int perf_trace_event_init(struct trace_event_call *tp_event,
				 struct perf_event *p_event)
{
	int ret;

	ret = perf_trace_event_perm(tp_event, p_event);
	if (ret)
		return ret;

	ret = perf_trace_event_reg(tp_event, p_event);
	if (ret)
		return ret;

	ret = perf_trace_event_open(p_event);
	if (ret) {
		perf_trace_event_unreg(p_event);
		return ret;
	}

	return 0;
}