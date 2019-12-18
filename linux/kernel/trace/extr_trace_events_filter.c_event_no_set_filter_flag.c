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
struct trace_event_file {int flags; } ;

/* Variables and functions */
 int EVENT_FILE_FL_NO_SET_FILTER ; 

__attribute__((used)) static inline bool
event_no_set_filter_flag(struct trace_event_file *file)
{
	if (file->flags & EVENT_FILE_FL_NO_SET_FILTER)
		return true;

	return false;
}