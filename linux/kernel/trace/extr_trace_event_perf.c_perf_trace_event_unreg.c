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
struct trace_event_call {scalar_t__ perf_refcount; int /*<<< orphan*/  mod; int /*<<< orphan*/ * perf_events; TYPE_1__* class; } ;
struct perf_event {struct trace_event_call* tp_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reg ) (struct trace_event_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int PERF_NR_CONTEXTS ; 
 int /*<<< orphan*/  TRACE_REG_PERF_UNREGISTER ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** perf_trace_buf ; 
 int /*<<< orphan*/  stub1 (struct trace_event_call*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  total_ref_count ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 

__attribute__((used)) static void perf_trace_event_unreg(struct perf_event *p_event)
{
	struct trace_event_call *tp_event = p_event->tp_event;
	int i;

	if (--tp_event->perf_refcount > 0)
		goto out;

	tp_event->class->reg(tp_event, TRACE_REG_PERF_UNREGISTER, NULL);

	/*
	 * Ensure our callback won't be called anymore. The buffers
	 * will be freed after that.
	 */
	tracepoint_synchronize_unregister();

	free_percpu(tp_event->perf_events);
	tp_event->perf_events = NULL;

	if (!--total_ref_count) {
		for (i = 0; i < PERF_NR_CONTEXTS; i++) {
			free_percpu(perf_trace_buf[i]);
			perf_trace_buf[i] = NULL;
		}
	}
out:
	module_put(tp_event->mod);
}