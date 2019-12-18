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
typedef  scalar_t__ u64 ;
struct trace_iterator {TYPE_1__* trace_buffer; } ;
struct ring_buffer_iter {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct TYPE_4__ {unsigned long skipped_entries; } ;
struct TYPE_3__ {scalar_t__ time_start; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 TYPE_2__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 struct ring_buffer_event* ring_buffer_iter_peek (struct ring_buffer_iter*,scalar_t__*) ; 
 int /*<<< orphan*/  ring_buffer_iter_reset (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  ring_buffer_read (struct ring_buffer_iter*,int /*<<< orphan*/ *) ; 
 struct ring_buffer_iter* trace_buffer_iter (struct trace_iterator*,int) ; 

void tracing_iter_reset(struct trace_iterator *iter, int cpu)
{
	struct ring_buffer_event *event;
	struct ring_buffer_iter *buf_iter;
	unsigned long entries = 0;
	u64 ts;

	per_cpu_ptr(iter->trace_buffer->data, cpu)->skipped_entries = 0;

	buf_iter = trace_buffer_iter(iter, cpu);
	if (!buf_iter)
		return;

	ring_buffer_iter_reset(buf_iter);

	/*
	 * We could have the case with the max latency tracers
	 * that a reset never took place on a cpu. This is evident
	 * by the timestamp being before the start of the buffer.
	 */
	while ((event = ring_buffer_iter_peek(buf_iter, &ts))) {
		if (ts >= iter->trace_buffer->time_start)
			break;
		entries++;
		ring_buffer_read(buf_iter, NULL);
	}

	per_cpu_ptr(iter->trace_buffer->data, cpu)->skipped_entries = entries;
}