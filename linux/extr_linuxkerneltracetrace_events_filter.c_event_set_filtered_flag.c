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
struct trace_event_file {unsigned long flags; } ;

/* Variables and functions */
 unsigned long EVENT_FILE_FL_FILTERED ; 
 int /*<<< orphan*/  trace_buffered_event_enable () ; 

__attribute__((used)) static inline void event_set_filtered_flag(struct trace_event_file *file)
{
	unsigned long old_flags = file->flags;

	file->flags |= EVENT_FILE_FL_FILTERED;

	if (old_flags != file->flags)
		trace_buffered_event_enable();
}