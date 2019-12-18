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
struct event_trigger_data {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  hist_enable_trigger (struct event_trigger_data*,void*,struct ring_buffer_event*) ; 

__attribute__((used)) static void
hist_enable_count_trigger(struct event_trigger_data *data, void *rec,
			  struct ring_buffer_event *event)
{
	if (!data->count)
		return;

	if (data->count != -1)
		(data->count)--;

	hist_enable_trigger(data, rec, event);
}