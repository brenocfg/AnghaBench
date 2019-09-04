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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  u32 ;
struct trace_event_call {int dummy; } ;
struct TYPE_2__ {struct ring_buffer* buffer; } ;
struct trace_array {TYPE_1__ trace_buffer; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct bprint_entry {unsigned long ip; char const* fmt; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_BPRINT ; 
 int TRACE_BUF_SIZE ; 
 int /*<<< orphan*/  __buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 struct ring_buffer_event* __trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  call_filter_check_discard (struct trace_event_call*,struct bprint_entry*,struct ring_buffer*,struct ring_buffer_event*) ; 
 struct trace_event_call event_bprint ; 
 int /*<<< orphan*/  ftrace_trace_stack (struct trace_array*,struct ring_buffer*,unsigned long,int,int,int /*<<< orphan*/ *) ; 
 char* get_trace_buf () ; 
 struct trace_array global_trace ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pause_graph_tracing () ; 
 int preempt_count () ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int /*<<< orphan*/  put_trace_buf () ; 
 struct bprint_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 scalar_t__ tracing_disabled ; 
 scalar_t__ tracing_selftest_running ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unpause_graph_tracing () ; 
 int vbin_printf (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 

int trace_vbprintk(unsigned long ip, const char *fmt, va_list args)
{
	struct trace_event_call *call = &event_bprint;
	struct ring_buffer_event *event;
	struct ring_buffer *buffer;
	struct trace_array *tr = &global_trace;
	struct bprint_entry *entry;
	unsigned long flags;
	char *tbuffer;
	int len = 0, size, pc;

	if (unlikely(tracing_selftest_running || tracing_disabled))
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

	len = vbin_printf((u32 *)tbuffer, TRACE_BUF_SIZE/sizeof(int), fmt, args);

	if (len > TRACE_BUF_SIZE/sizeof(int) || len < 0)
		goto out;

	local_save_flags(flags);
	size = sizeof(*entry) + sizeof(u32) * len;
	buffer = tr->trace_buffer.buffer;
	event = __trace_buffer_lock_reserve(buffer, TRACE_BPRINT, size,
					    flags, pc);
	if (!event)
		goto out;
	entry = ring_buffer_event_data(event);
	entry->ip			= ip;
	entry->fmt			= fmt;

	memcpy(entry->buf, tbuffer, sizeof(u32) * len);
	if (!call_filter_check_discard(call, entry, buffer, event)) {
		__buffer_unlock_commit(buffer, event);
		ftrace_trace_stack(tr, buffer, flags, 6, pc, NULL);
	}

out:
	put_trace_buf();

out_nobuffer:
	preempt_enable_notrace();
	unpause_graph_tracing();

	return len;
}