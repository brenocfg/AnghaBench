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
struct hist_trigger_data {int /*<<< orphan*/  map; } ;
struct event_trigger_data {scalar_t__ name; struct hist_trigger_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pause_named_trigger (struct event_trigger_data*) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 
 int /*<<< orphan*/  tracing_map_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpause_named_trigger (struct event_trigger_data*) ; 

__attribute__((used)) static void hist_clear(struct event_trigger_data *data)
{
	struct hist_trigger_data *hist_data = data->private_data;

	if (data->name)
		pause_named_trigger(data);

	tracepoint_synchronize_unregister();

	tracing_map_clear(hist_data->map);

	if (data->name)
		unpause_named_trigger(data);
}