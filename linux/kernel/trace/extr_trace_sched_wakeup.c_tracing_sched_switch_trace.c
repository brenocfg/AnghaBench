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
struct task_struct {int /*<<< orphan*/  prio; int /*<<< orphan*/  pid; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct ctx_switch_entry {int /*<<< orphan*/  next_cpu; void* next_state; int /*<<< orphan*/  next_prio; int /*<<< orphan*/  next_pid; void* prev_state; int /*<<< orphan*/  prev_prio; int /*<<< orphan*/  prev_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_CTX ; 
 int /*<<< orphan*/  call_filter_check_discard (struct trace_event_call*,struct ctx_switch_entry*,struct ring_buffer*,struct ring_buffer_event*) ; 
 struct trace_event_call event_context_switch ; 
 struct ctx_switch_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  task_cpu (struct task_struct*) ; 
 void* task_state_index (struct task_struct*) ; 
 struct ring_buffer_event* trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  trace_buffer_unlock_commit (struct trace_array*,struct ring_buffer*,struct ring_buffer_event*,unsigned long,int) ; 

__attribute__((used)) static void
tracing_sched_switch_trace(struct trace_array *tr,
			   struct task_struct *prev,
			   struct task_struct *next,
			   unsigned long flags, int pc)
{
	struct trace_event_call *call = &event_context_switch;
	struct ring_buffer *buffer = tr->trace_buffer.buffer;
	struct ring_buffer_event *event;
	struct ctx_switch_entry *entry;

	event = trace_buffer_lock_reserve(buffer, TRACE_CTX,
					  sizeof(*entry), flags, pc);
	if (!event)
		return;
	entry	= ring_buffer_event_data(event);
	entry->prev_pid			= prev->pid;
	entry->prev_prio		= prev->prio;
	entry->prev_state		= task_state_index(prev);
	entry->next_pid			= next->pid;
	entry->next_prio		= next->prio;
	entry->next_state		= task_state_index(next);
	entry->next_cpu	= task_cpu(next);

	if (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(tr, buffer, event, flags, pc);
}