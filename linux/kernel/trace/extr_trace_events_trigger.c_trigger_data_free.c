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
struct event_trigger_data {TYPE_1__* cmd_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_filter ) (int /*<<< orphan*/ *,struct event_trigger_data*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct event_trigger_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct event_trigger_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 

void trigger_data_free(struct event_trigger_data *data)
{
	if (data->cmd_ops->set_filter)
		data->cmd_ops->set_filter(NULL, data, NULL);

	/* make sure current triggers exit before free */
	tracepoint_synchronize_unregister();

	kfree(data);
}