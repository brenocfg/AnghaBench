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
struct ring_buffer_event {int type_len; int* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int RB_EVNT_HDR_SIZE ; 
 int RB_LEN_TIME_EXTEND ; 
 int RB_LEN_TIME_STAMP ; 
#define  RINGBUF_TYPE_DATA 131 
#define  RINGBUF_TYPE_PADDING 130 
#define  RINGBUF_TYPE_TIME_EXTEND 129 
#define  RINGBUF_TYPE_TIME_STAMP 128 
 int rb_event_data_length (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  rb_null_event (struct ring_buffer_event*) ; 

__attribute__((used)) static inline unsigned
rb_event_length(struct ring_buffer_event *event)
{
	switch (event->type_len) {
	case RINGBUF_TYPE_PADDING:
		if (rb_null_event(event))
			/* undefined */
			return -1;
		return  event->array[0] + RB_EVNT_HDR_SIZE;

	case RINGBUF_TYPE_TIME_EXTEND:
		return RB_LEN_TIME_EXTEND;

	case RINGBUF_TYPE_TIME_STAMP:
		return RB_LEN_TIME_STAMP;

	case RINGBUF_TYPE_DATA:
		return rb_event_data_length(event);
	default:
		BUG();
	}
	/* not hit */
	return 0;
}