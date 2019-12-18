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
struct ring_buffer_per_cpu {int /*<<< orphan*/  read_stamp; } ;
struct ring_buffer_event {int type_len; int /*<<< orphan*/  time_delta; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RINGBUF_TYPE_DATA 131 
#define  RINGBUF_TYPE_PADDING 130 
#define  RINGBUF_TYPE_TIME_EXTEND 129 
#define  RINGBUF_TYPE_TIME_STAMP 128 
 int /*<<< orphan*/  ring_buffer_event_time_stamp (struct ring_buffer_event*) ; 

__attribute__((used)) static void
rb_update_read_stamp(struct ring_buffer_per_cpu *cpu_buffer,
		     struct ring_buffer_event *event)
{
	u64 delta;

	switch (event->type_len) {
	case RINGBUF_TYPE_PADDING:
		return;

	case RINGBUF_TYPE_TIME_EXTEND:
		delta = ring_buffer_event_time_stamp(event);
		cpu_buffer->read_stamp += delta;
		return;

	case RINGBUF_TYPE_TIME_STAMP:
		delta = ring_buffer_event_time_stamp(event);
		cpu_buffer->read_stamp = delta;
		return;

	case RINGBUF_TYPE_DATA:
		cpu_buffer->read_stamp += event->time_delta;
		return;

	default:
		BUG();
	}
	return;
}