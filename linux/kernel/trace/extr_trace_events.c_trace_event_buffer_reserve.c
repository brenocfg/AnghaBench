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
struct trace_event_file {int flags; struct trace_event_call* event_call; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct trace_event_call {TYPE_1__ event; } ;
struct trace_event_buffer {void* entry; int /*<<< orphan*/  event; int /*<<< orphan*/  pc; int /*<<< orphan*/  flags; int /*<<< orphan*/  buffer; struct trace_event_file* trace_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPTION ; 
 int EVENT_FILE_FL_PID_FILTER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_save_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_count () ; 
 void* ring_buffer_event_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_event_buffer_lock_reserve (int /*<<< orphan*/ *,struct trace_event_file*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ trace_event_ignore_this_pid (struct trace_event_file*) ; 

void *trace_event_buffer_reserve(struct trace_event_buffer *fbuffer,
				 struct trace_event_file *trace_file,
				 unsigned long len)
{
	struct trace_event_call *event_call = trace_file->event_call;

	if ((trace_file->flags & EVENT_FILE_FL_PID_FILTER) &&
	    trace_event_ignore_this_pid(trace_file))
		return NULL;

	local_save_flags(fbuffer->flags);
	fbuffer->pc = preempt_count();
	/*
	 * If CONFIG_PREEMPTION is enabled, then the tracepoint itself disables
	 * preemption (adding one to the preempt_count). Since we are
	 * interested in the preempt_count at the time the tracepoint was
	 * hit, we need to subtract one to offset the increment.
	 */
	if (IS_ENABLED(CONFIG_PREEMPTION))
		fbuffer->pc--;
	fbuffer->trace_file = trace_file;

	fbuffer->event =
		trace_event_buffer_lock_reserve(&fbuffer->buffer, trace_file,
						event_call->event.type, len,
						fbuffer->flags, fbuffer->pc);
	if (!fbuffer->event)
		return NULL;

	fbuffer->entry = ring_buffer_event_data(fbuffer->event);
	return fbuffer->entry;
}