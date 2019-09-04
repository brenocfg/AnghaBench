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
struct trace_event_call {TYPE_1__* class; } ;
struct perf_event {struct trace_event_call* tp_event; } ;
struct TYPE_2__ {int (* reg ) (struct trace_event_call*,int /*<<< orphan*/ ,struct perf_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_REG_PERF_OPEN ; 
 int stub1 (struct trace_event_call*,int /*<<< orphan*/ ,struct perf_event*) ; 

__attribute__((used)) static int perf_trace_event_open(struct perf_event *p_event)
{
	struct trace_event_call *tp_event = p_event->tp_event;
	return tp_event->class->reg(tp_event, TRACE_REG_PERF_OPEN, p_event);
}