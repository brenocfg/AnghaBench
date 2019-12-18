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
struct trace_event_call {int dummy; } ;
struct TYPE_2__ {struct ring_buffer* buffer; } ;
struct trace_array {TYPE_1__ trace_buffer; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ftrace_graph_ret {int dummy; } ;
struct ftrace_graph_ret_entry {struct ftrace_graph_ret ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_GRAPH_RET ; 
 int /*<<< orphan*/  call_filter_check_discard (struct trace_event_call*,struct ftrace_graph_ret_entry*,struct ring_buffer*,struct ring_buffer_event*) ; 
 struct trace_event_call event_funcgraph_exit ; 
 struct ftrace_graph_ret_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  trace_buffer_unlock_commit_nostack (struct ring_buffer*,struct ring_buffer_event*) ; 

void __trace_graph_return(struct trace_array *tr,
				struct ftrace_graph_ret *trace,
				unsigned long flags,
				int pc)
{
	struct trace_event_call *call = &event_funcgraph_exit;
	struct ring_buffer_event *event;
	struct ring_buffer *buffer = tr->trace_buffer.buffer;
	struct ftrace_graph_ret_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_GRAPH_RET,
					  sizeof(*entry), flags, pc);
	if (!event)
		return;
	entry	= ring_buffer_event_data(event);
	entry->ret				= *trace;
	if (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit_nostack(buffer, event);
}