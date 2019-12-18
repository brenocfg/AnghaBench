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
struct tracing_map_elt {int dummy; } ;
struct seq_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_actions; struct action_data** actions; } ;
struct action_data {scalar_t__ action; scalar_t__ handler; } ;

/* Variables and functions */
 scalar_t__ ACTION_SNAPSHOT ; 
 scalar_t__ HANDLER_ONCHANGE ; 
 scalar_t__ HANDLER_ONMAX ; 
 int /*<<< orphan*/  track_data_print (struct seq_file*,struct hist_trigger_data*,struct tracing_map_elt*,struct action_data*) ; 

__attribute__((used)) static void print_actions(struct seq_file *m,
			  struct hist_trigger_data *hist_data,
			  struct tracing_map_elt *elt)
{
	unsigned int i;

	for (i = 0; i < hist_data->n_actions; i++) {
		struct action_data *data = hist_data->actions[i];

		if (data->action == ACTION_SNAPSHOT)
			continue;

		if (data->handler == HANDLER_ONMAX ||
		    data->handler == HANDLER_ONCHANGE)
			track_data_print(m, hist_data, elt, data);
	}
}