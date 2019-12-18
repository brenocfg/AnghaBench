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
struct ring_buffer_per_cpu {scalar_t__ lost_events; } ;
struct ring_buffer_event {scalar_t__ type_len; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 scalar_t__ RINGBUF_TYPE_PADDING ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rb_advance_reader (struct ring_buffer_per_cpu*) ; 
 struct ring_buffer_event* rb_buffer_peek (struct ring_buffer_per_cpu*,int /*<<< orphan*/ *,unsigned long*) ; 
 int rb_reader_lock (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_reader_unlock (struct ring_buffer_per_cpu*,int) ; 

struct ring_buffer_event *
ring_buffer_consume(struct ring_buffer *buffer, int cpu, u64 *ts,
		    unsigned long *lost_events)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	struct ring_buffer_event *event = NULL;
	unsigned long flags;
	bool dolock;

 again:
	/* might be called in atomic */
	preempt_disable();

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		goto out;

	cpu_buffer = buffer->buffers[cpu];
	local_irq_save(flags);
	dolock = rb_reader_lock(cpu_buffer);

	event = rb_buffer_peek(cpu_buffer, ts, lost_events);
	if (event) {
		cpu_buffer->lost_events = 0;
		rb_advance_reader(cpu_buffer);
	}

	rb_reader_unlock(cpu_buffer, dolock);
	local_irq_restore(flags);

 out:
	preempt_enable();

	if (event && event->type_len == RINGBUF_TYPE_PADDING)
		goto again;

	return event;
}