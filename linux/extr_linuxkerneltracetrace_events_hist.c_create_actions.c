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
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {struct action_data** actions; TYPE_1__* attrs; } ;
struct action_data {scalar_t__ fn; } ;
struct TYPE_2__ {unsigned int n_actions; } ;

/* Variables and functions */
 scalar_t__ action_trace ; 
 int onmatch_create (struct hist_trigger_data*,struct trace_event_file*,struct action_data*) ; 
 int onmax_create (struct hist_trigger_data*,struct action_data*) ; 
 scalar_t__ onmax_save ; 

__attribute__((used)) static int create_actions(struct hist_trigger_data *hist_data,
			  struct trace_event_file *file)
{
	struct action_data *data;
	unsigned int i;
	int ret = 0;

	for (i = 0; i < hist_data->attrs->n_actions; i++) {
		data = hist_data->actions[i];

		if (data->fn == action_trace) {
			ret = onmatch_create(hist_data, file, data);
			if (ret)
				return ret;
		} else if (data->fn == onmax_save) {
			ret = onmax_create(hist_data, data);
			if (ret)
				return ret;
		}
	}

	return ret;
}