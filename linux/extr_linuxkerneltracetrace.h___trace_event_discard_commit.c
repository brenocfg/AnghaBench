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
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ring_buffer_discard_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 struct ring_buffer_event* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_buffered_event ; 
 int /*<<< orphan*/  trace_buffered_event_cnt ; 

__attribute__((used)) static inline void
__trace_event_discard_commit(struct ring_buffer *buffer,
			     struct ring_buffer_event *event)
{
	if (this_cpu_read(trace_buffered_event) == event) {
		/* Simply release the temp buffer */
		this_cpu_dec(trace_buffered_event_cnt);
		return;
	}
	ring_buffer_discard_commit(buffer, event);
}