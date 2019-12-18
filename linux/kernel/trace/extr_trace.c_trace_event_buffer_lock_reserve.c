#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trace_event_file {int flags; TYPE_2__* tr; } ;
struct ring_buffer_event {unsigned long* array; } ;
struct ring_buffer {int dummy; } ;
struct TYPE_3__ {struct ring_buffer* buffer; } ;
struct TYPE_4__ {TYPE_1__ trace_buffer; } ;

/* Variables and functions */
 int EVENT_FILE_FL_FILTERED ; 
 int EVENT_FILE_FL_SOFT_DISABLED ; 
 int EVENT_FILE_FL_TRIGGER_COND ; 
 struct ring_buffer_event* __trace_buffer_lock_reserve (struct ring_buffer*,int,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  ring_buffer_time_stamp_abs (struct ring_buffer*) ; 
 struct ring_buffer* temp_buffer ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 int this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 struct ring_buffer_event* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_buffered_event ; 
 int /*<<< orphan*/  trace_buffered_event_cnt ; 
 int /*<<< orphan*/  trace_event_setup (struct ring_buffer_event*,int,unsigned long,int) ; 

struct ring_buffer_event *
trace_event_buffer_lock_reserve(struct ring_buffer **current_rb,
			  struct trace_event_file *trace_file,
			  int type, unsigned long len,
			  unsigned long flags, int pc)
{
	struct ring_buffer_event *entry;
	int val;

	*current_rb = trace_file->tr->trace_buffer.buffer;

	if (!ring_buffer_time_stamp_abs(*current_rb) && (trace_file->flags &
	     (EVENT_FILE_FL_SOFT_DISABLED | EVENT_FILE_FL_FILTERED)) &&
	    (entry = this_cpu_read(trace_buffered_event))) {
		/* Try to use the per cpu buffer first */
		val = this_cpu_inc_return(trace_buffered_event_cnt);
		if (val == 1) {
			trace_event_setup(entry, type, flags, pc);
			entry->array[0] = len;
			return entry;
		}
		this_cpu_dec(trace_buffered_event_cnt);
	}

	entry = __trace_buffer_lock_reserve(*current_rb,
					    type, len, flags, pc);
	/*
	 * If tracing is off, but we have triggers enabled
	 * we still need to look at the event data. Use the temp_buffer
	 * to store the trace event for the tigger to use. It's recusive
	 * safe and will not be recorded anywhere.
	 */
	if (!entry && trace_file->flags & EVENT_FILE_FL_TRIGGER_COND) {
		*current_rb = temp_buffer;
		entry = __trace_buffer_lock_reserve(*current_rb,
						    type, len, flags, pc);
	}
	return entry;
}