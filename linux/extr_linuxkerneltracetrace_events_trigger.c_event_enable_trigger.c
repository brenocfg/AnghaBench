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
struct event_trigger_data {struct enable_trigger_data* private_data; } ;
struct enable_trigger_data {TYPE_1__* file; scalar_t__ enable; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_FILE_FL_SOFT_DISABLED_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
event_enable_trigger(struct event_trigger_data *data, void *rec,
		     struct ring_buffer_event *event)
{
	struct enable_trigger_data *enable_data = data->private_data;

	if (enable_data->enable)
		clear_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &enable_data->file->flags);
	else
		set_bit(EVENT_FILE_FL_SOFT_DISABLED_BIT, &enable_data->file->flags);
}