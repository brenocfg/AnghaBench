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
typedef  scalar_t__ u64 ;
struct ring_buffer_per_cpu {scalar_t__ read; scalar_t__ reader_page; int /*<<< orphan*/  cpu; struct ring_buffer* buffer; } ;
struct ring_buffer_iter {scalar_t__ cache_read; scalar_t__ cache_reader_page; scalar_t__ head; scalar_t__ read_stamp; int /*<<< orphan*/  head_page; struct ring_buffer_per_cpu* cpu_buffer; } ;
struct ring_buffer_event {int type_len; scalar_t__ time_delta; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
#define  RINGBUF_TYPE_DATA 131 
#define  RINGBUF_TYPE_PADDING 130 
#define  RINGBUF_TYPE_TIME_EXTEND 129 
#define  RINGBUF_TYPE_TIME_STAMP 128 
 int /*<<< orphan*/  rb_advance_iter (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  rb_inc_iter (struct ring_buffer_iter*) ; 
 struct ring_buffer_event* rb_iter_head_event (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  rb_iter_reset (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  rb_null_event (struct ring_buffer_event*) ; 
 scalar_t__ rb_page_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rb_per_cpu_empty (struct ring_buffer_per_cpu*) ; 
 scalar_t__ ring_buffer_event_time_stamp (struct ring_buffer_event*) ; 
 scalar_t__ ring_buffer_iter_empty (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  ring_buffer_normalize_time_stamp (struct ring_buffer*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ring_buffer_event *
rb_iter_peek(struct ring_buffer_iter *iter, u64 *ts)
{
	struct ring_buffer *buffer;
	struct ring_buffer_per_cpu *cpu_buffer;
	struct ring_buffer_event *event;
	int nr_loops = 0;

	if (ts)
		*ts = 0;

	cpu_buffer = iter->cpu_buffer;
	buffer = cpu_buffer->buffer;

	/*
	 * Check if someone performed a consuming read to
	 * the buffer. A consuming read invalidates the iterator
	 * and we need to reset the iterator in this case.
	 */
	if (unlikely(iter->cache_read != cpu_buffer->read ||
		     iter->cache_reader_page != cpu_buffer->reader_page))
		rb_iter_reset(iter);

 again:
	if (ring_buffer_iter_empty(iter))
		return NULL;

	/*
	 * We repeat when a time extend is encountered or we hit
	 * the end of the page. Since the time extend is always attached
	 * to a data event, we should never loop more than three times.
	 * Once for going to next page, once on time extend, and
	 * finally once to get the event.
	 * (We never hit the following condition more than thrice).
	 */
	if (RB_WARN_ON(cpu_buffer, ++nr_loops > 3))
		return NULL;

	if (rb_per_cpu_empty(cpu_buffer))
		return NULL;

	if (iter->head >= rb_page_size(iter->head_page)) {
		rb_inc_iter(iter);
		goto again;
	}

	event = rb_iter_head_event(iter);

	switch (event->type_len) {
	case RINGBUF_TYPE_PADDING:
		if (rb_null_event(event)) {
			rb_inc_iter(iter);
			goto again;
		}
		rb_advance_iter(iter);
		return event;

	case RINGBUF_TYPE_TIME_EXTEND:
		/* Internal data, OK to advance */
		rb_advance_iter(iter);
		goto again;

	case RINGBUF_TYPE_TIME_STAMP:
		if (ts) {
			*ts = ring_buffer_event_time_stamp(event);
			ring_buffer_normalize_time_stamp(cpu_buffer->buffer,
							 cpu_buffer->cpu, ts);
		}
		/* Internal data, OK to advance */
		rb_advance_iter(iter);
		goto again;

	case RINGBUF_TYPE_DATA:
		if (ts && !(*ts)) {
			*ts = iter->read_stamp + event->time_delta;
			ring_buffer_normalize_time_stamp(buffer,
							 cpu_buffer->cpu, ts);
		}
		return event;

	default:
		BUG();
	}

	return NULL;
}