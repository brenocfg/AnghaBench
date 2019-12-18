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
struct ring_buffer_per_cpu {int /*<<< orphan*/  cpu; int /*<<< orphan*/  buffer; scalar_t__ read_stamp; } ;
struct ring_buffer_event {int type_len; scalar_t__ time_delta; } ;
struct buffer_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
#define  RINGBUF_TYPE_DATA 131 
#define  RINGBUF_TYPE_PADDING 130 
#define  RINGBUF_TYPE_TIME_EXTEND 129 
#define  RINGBUF_TYPE_TIME_STAMP 128 
 int /*<<< orphan*/  rb_advance_reader (struct ring_buffer_per_cpu*) ; 
 struct buffer_page* rb_get_reader_page (struct ring_buffer_per_cpu*) ; 
 unsigned long rb_lost_events (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_null_event (struct ring_buffer_event*) ; 
 struct ring_buffer_event* rb_reader_event (struct ring_buffer_per_cpu*) ; 
 scalar_t__ ring_buffer_event_time_stamp (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  ring_buffer_normalize_time_stamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static struct ring_buffer_event *
rb_buffer_peek(struct ring_buffer_per_cpu *cpu_buffer, u64 *ts,
	       unsigned long *lost_events)
{
	struct ring_buffer_event *event;
	struct buffer_page *reader;
	int nr_loops = 0;

	if (ts)
		*ts = 0;
 again:
	/*
	 * We repeat when a time extend is encountered.
	 * Since the time extend is always attached to a data event,
	 * we should never loop more than once.
	 * (We never hit the following condition more than twice).
	 */
	if (RB_WARN_ON(cpu_buffer, ++nr_loops > 2))
		return NULL;

	reader = rb_get_reader_page(cpu_buffer);
	if (!reader)
		return NULL;

	event = rb_reader_event(cpu_buffer);

	switch (event->type_len) {
	case RINGBUF_TYPE_PADDING:
		if (rb_null_event(event))
			RB_WARN_ON(cpu_buffer, 1);
		/*
		 * Because the writer could be discarding every
		 * event it creates (which would probably be bad)
		 * if we were to go back to "again" then we may never
		 * catch up, and will trigger the warn on, or lock
		 * the box. Return the padding, and we will release
		 * the current locks, and try again.
		 */
		return event;

	case RINGBUF_TYPE_TIME_EXTEND:
		/* Internal data, OK to advance */
		rb_advance_reader(cpu_buffer);
		goto again;

	case RINGBUF_TYPE_TIME_STAMP:
		if (ts) {
			*ts = ring_buffer_event_time_stamp(event);
			ring_buffer_normalize_time_stamp(cpu_buffer->buffer,
							 cpu_buffer->cpu, ts);
		}
		/* Internal data, OK to advance */
		rb_advance_reader(cpu_buffer);
		goto again;

	case RINGBUF_TYPE_DATA:
		if (ts && !(*ts)) {
			*ts = cpu_buffer->read_stamp + event->time_delta;
			ring_buffer_normalize_time_stamp(cpu_buffer->buffer,
							 cpu_buffer->cpu, ts);
		}
		if (lost_events)
			*lost_events = rb_lost_events(cpu_buffer);
		return event;

	default:
		BUG();
	}

	return NULL;
}