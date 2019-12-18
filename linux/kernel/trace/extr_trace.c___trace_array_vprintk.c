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
typedef  int /*<<< orphan*/  va_list ;
struct trace_event_call {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct print_entry {unsigned long ip; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_BUF_SIZE ; 
 int /*<<< orphan*/  TRACE_PRINT ; 
 int /*<<< orphan*/  __buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 struct ring_buffer_event* __trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  call_filter_check_discard (struct trace_event_call*,struct print_entry*,struct ring_buffer*,struct ring_buffer_event*) ; 
 struct trace_event_call event_print ; 
 int /*<<< orphan*/  ftrace_trace_stack (int /*<<< orphan*/ *,struct ring_buffer*,unsigned long,int,int,int /*<<< orphan*/ *) ; 
 char* get_trace_buf () ; 
 int /*<<< orphan*/  global_trace ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pause_graph_tracing () ; 
 int preempt_count () ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int /*<<< orphan*/  put_trace_buf () ; 
 struct print_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 scalar_t__ tracing_disabled ; 
 scalar_t__ tracing_selftest_running ; 
 int /*<<< orphan*/  unpause_graph_tracing () ; 
 int vscnprintf (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__trace_array_vprintk(struct ring_buffer *buffer,
		      unsigned long ip, const char *fmt, va_list args)
{
	struct trace_event_call *call = &event_print;
	struct ring_buffer_event *event;
	int len = 0, size, pc;
	struct print_entry *entry;
	unsigned long flags;
	char *tbuffer;

	if (tracing_disabled || tracing_selftest_running)
		return 0;

	/* Don't pollute graph traces with trace_vprintk internals */
	pause_graph_tracing();

	pc = preempt_count();
	preempt_disable_notrace();


	tbuffer = get_trace_buf();
	if (!tbuffer) {
		len = 0;
		goto out_nobuffer;
	}

	len = vscnprintf(tbuffer, TRACE_BUF_SIZE, fmt, args);

	local_save_flags(flags);
	size = sizeof(*entry) + len + 1;
	event = __trace_buffer_lock_reserve(buffer, TRACE_PRINT, size,
					    flags, pc);
	if (!event)
		goto out;
	entry = ring_buffer_event_data(event);
	entry->ip = ip;

	memcpy(&entry->buf, tbuffer, len + 1);
	if (!call_filter_check_discard(call, entry, buffer, event)) {
		__buffer_unlock_commit(buffer, event);
		ftrace_trace_stack(&global_trace, buffer, flags, 6, pc, NULL);
	}

out:
	put_trace_buf();

out_nobuffer:
	preempt_enable_notrace();
	unpause_graph_tracing();

	return len;
}