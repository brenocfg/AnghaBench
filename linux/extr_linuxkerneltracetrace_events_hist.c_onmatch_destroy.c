#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* synth_event; struct action_data* synth_event_name; struct action_data* match_event_system; struct action_data* match_event; } ;
struct action_data {unsigned int n_params; TYPE_2__ onmatch; struct action_data** params; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct action_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synth_event_mutex ; 

__attribute__((used)) static void onmatch_destroy(struct action_data *data)
{
	unsigned int i;

	mutex_lock(&synth_event_mutex);

	kfree(data->onmatch.match_event);
	kfree(data->onmatch.match_event_system);
	kfree(data->onmatch.synth_event_name);

	for (i = 0; i < data->n_params; i++)
		kfree(data->params[i]);

	if (data->onmatch.synth_event)
		data->onmatch.synth_event->ref--;

	kfree(data);

	mutex_unlock(&synth_event_mutex);
}