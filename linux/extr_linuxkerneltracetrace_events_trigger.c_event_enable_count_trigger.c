#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_event {int dummy; } ;
struct event_trigger_data {int count; struct enable_trigger_data* private_data; } ;
struct enable_trigger_data {int enable; TYPE_1__* file; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EVENT_FILE_FL_SOFT_DISABLED ; 
 int /*<<< orphan*/  event_enable_trigger (struct event_trigger_data*,void*,struct ring_buffer_event*) ; 

__attribute__((used)) static void
event_enable_count_trigger(struct event_trigger_data *data, void *rec,
			   struct ring_buffer_event *event)
{
	struct enable_trigger_data *enable_data = data->private_data;

	if (!data->count)
		return;

	/* Skip if the event is in a state we want to switch to */
	if (enable_data->enable == !(enable_data->file->flags & EVENT_FILE_FL_SOFT_DISABLED))
		return;

	if (data->count != -1)
		(data->count)--;

	event_enable_trigger(data, rec, event);
}