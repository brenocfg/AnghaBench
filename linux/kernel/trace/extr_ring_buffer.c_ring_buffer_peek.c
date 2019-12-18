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
typedef  int /*<<< orphan*/  u64 ;
struct ring_buffer_per_cpu {int dummy; } ;
struct ring_buffer_event {scalar_t__ type_len; } ;
struct ring_buffer {int /*<<< orphan*/  cpumask; struct ring_buffer_per_cpu** buffers; } ;

/* Variables and functions */
 scalar_t__ RINGBUF_TYPE_PADDING ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rb_advance_reader (struct ring_buffer_per_cpu*) ; 
 struct ring_buffer_event* rb_buffer_peek (struct ring_buffer_per_cpu*,int /*<<< orphan*/ *,unsigned long*) ; 
 int rb_reader_lock (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_reader_unlock (struct ring_buffer_per_cpu*,int) ; 

struct ring_buffer_event *
ring_buffer_peek(struct ring_buffer *buffer, int cpu, u64 *ts,
		 unsigned long *lost_events)
{
	struct ring_buffer_per_cpu *cpu_buffer = buffer->buffers[cpu];
	struct ring_buffer_event *event;
	unsigned long flags;
	bool dolock;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return NULL;

 again:
	local_irq_save(flags);
	dolock = rb_reader_lock(cpu_buffer);
	event = rb_buffer_peek(cpu_buffer, ts, lost_events);
	if (event && event->type_len == RINGBUF_TYPE_PADDING)
		rb_advance_reader(cpu_buffer);
	rb_reader_unlock(cpu_buffer, dolock);
	local_irq_restore(flags);

	if (event && event->type_len == RINGBUF_TYPE_PADDING)
		goto again;

	return event;
}