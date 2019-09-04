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
struct trace_event_call {int flags; int /*<<< orphan*/  filter; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 int TRACE_EVENT_FL_FILTERED ; 
 int /*<<< orphan*/  __trace_event_discard_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  filter_match_preds (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ unlikely (int) ; 

int call_filter_check_discard(struct trace_event_call *call, void *rec,
			      struct ring_buffer *buffer,
			      struct ring_buffer_event *event)
{
	if (unlikely(call->flags & TRACE_EVENT_FL_FILTERED) &&
	    !filter_match_preds(call->filter, rec)) {
		__trace_event_discard_commit(buffer, event);
		return 1;
	}

	return 0;
}