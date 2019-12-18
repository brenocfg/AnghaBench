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

/* Variables and functions */
 unsigned int RB_LEN_TIME_EXTEND ; 
 scalar_t__ extended_time (struct ring_buffer_event*) ; 
 int rb_event_length (struct ring_buffer_event*) ; 
 struct ring_buffer_event* skip_time_extend (struct ring_buffer_event*) ; 

__attribute__((used)) static inline unsigned
rb_event_ts_length(struct ring_buffer_event *event)
{
	unsigned len = 0;

	if (extended_time(event)) {
		/* time extends include the data event after it */
		len = RB_LEN_TIME_EXTEND;
		event = skip_time_extend(event);
	}
	return len + rb_event_length(event);
}