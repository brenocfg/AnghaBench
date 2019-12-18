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
struct action_data {unsigned int n_params; struct action_data* synth_event_name; TYPE_1__* synth_event; struct action_data** params; struct action_data* action_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  kfree (struct action_data*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void action_data_destroy(struct action_data *data)
{
	unsigned int i;

	lockdep_assert_held(&event_mutex);

	kfree(data->action_name);

	for (i = 0; i < data->n_params; i++)
		kfree(data->params[i]);

	if (data->synth_event)
		data->synth_event->ref--;

	kfree(data->synth_event_name);

	kfree(data);
}