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
struct event_trigger_data {struct event_trigger_data* named_data; } ;

/* Variables and functions */

struct event_trigger_data *
get_named_trigger_data(struct event_trigger_data *data)
{
	return data->named_data;
}