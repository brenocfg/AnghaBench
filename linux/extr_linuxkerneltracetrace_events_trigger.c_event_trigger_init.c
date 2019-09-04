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
struct event_trigger_ops {int dummy; } ;
struct event_trigger_data {int /*<<< orphan*/  ref; } ;

/* Variables and functions */

int event_trigger_init(struct event_trigger_ops *ops,
		       struct event_trigger_data *data)
{
	data->ref++;
	return 0;
}