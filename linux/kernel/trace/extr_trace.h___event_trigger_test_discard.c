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
struct trace_event_file {unsigned long flags; int /*<<< orphan*/  filter; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int dummy; } ;
typedef  enum event_trigger_type { ____Placeholder_event_trigger_type } event_trigger_type ;

/* Variables and functions */
 int EVENT_FILE_FL_FILTERED ; 
 int /*<<< orphan*/  EVENT_FILE_FL_SOFT_DISABLED_BIT ; 
 unsigned long EVENT_FILE_FL_TRIGGER_COND ; 
 int /*<<< orphan*/  __trace_event_discard_commit (struct ring_buffer*,struct ring_buffer_event*) ; 
 int event_triggers_call (struct trace_event_file*,void*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  filter_match_preds (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool
__event_trigger_test_discard(struct trace_event_file *file,
			     struct ring_buffer *buffer,
			     struct ring_buffer_event *event,
			     void *entry,
			     enum event_trigger_type *tt)
{
	unsigned long eflags = file->flags;

	if (eflags & EVENT_FILE_FL_TRIGGER_COND)
		*tt = event_triggers_call(file, entry, event);

	if (test_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &file->flags) ||
	    (unlikely(file->flags & EVENT_FILE_FL_FILTERED) &&
	     !filter_match_preds(file->filter, entry))) {
		__trace_event_discard_commit(buffer, event);
		return true;
	}

	return false;
}