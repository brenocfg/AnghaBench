#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
struct print_entry {unsigned long ip; char* buf; } ;
struct TYPE_4__ {struct ring_buffer* buffer; } ;
struct TYPE_5__ {int trace_flags; TYPE_1__ trace_buffer; } ;

/* Variables and functions */
 int TRACE_ITER_PRINTK ; 
 int /*<<< orphan*/  TRACE_PRINT ; 
 int /*<<< orphan*/  __buffer_unlock_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 struct ring_buffer_event* __trace_buffer_lock_reserve (struct ring_buffer*,int /*<<< orphan*/ ,int,unsigned long,int) ; 
 int /*<<< orphan*/  ftrace_trace_stack (TYPE_2__*,struct ring_buffer*,unsigned long,int,int,int /*<<< orphan*/ *) ; 
 TYPE_2__ global_trace ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 int /*<<< orphan*/  memcpy (char**,char const*,int) ; 
 int preempt_count () ; 
 struct print_entry* ring_buffer_event_data (struct ring_buffer_event*) ; 
 scalar_t__ tracing_disabled ; 
 scalar_t__ tracing_selftest_running ; 
 scalar_t__ unlikely (int) ; 

int __trace_puts(unsigned long ip, const char *str, int size)
{
	struct ring_buffer_event *event;
	struct ring_buffer *buffer;
	struct print_entry *entry;
	unsigned long irq_flags;
	int alloc;
	int pc;

	if (!(global_trace.trace_flags & TRACE_ITER_PRINTK))
		return 0;

	pc = preempt_count();

	if (unlikely(tracing_selftest_running || tracing_disabled))
		return 0;

	alloc = sizeof(*entry) + size + 2; /* possible \n added */

	local_save_flags(irq_flags);
	buffer = global_trace.trace_buffer.buffer;
	event = __trace_buffer_lock_reserve(buffer, TRACE_PRINT, alloc, 
					    irq_flags, pc);
	if (!event)
		return 0;

	entry = ring_buffer_event_data(event);
	entry->ip = ip;

	memcpy(&entry->buf, str, size);

	/* Add a newline if necessary */
	if (entry->buf[size - 1] != '\n') {
		entry->buf[size] = '\n';
		entry->buf[size + 1] = '\0';
	} else
		entry->buf[size] = '\0';

	__buffer_unlock_commit(buffer, event);
	ftrace_trace_stack(&global_trace, buffer, irq_flags, 4, pc, NULL);

	return size;
}