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
struct hist_trigger_data {unsigned int n_actions; struct action_data** actions; } ;
struct TYPE_4__ {int /*<<< orphan*/  fn_name; int /*<<< orphan*/  var_str; } ;
struct TYPE_3__ {int /*<<< orphan*/  match_event; int /*<<< orphan*/  match_event_system; int /*<<< orphan*/  synth_event_name; } ;
struct action_data {scalar_t__ fn; unsigned int n_params; TYPE_2__ onmax; TYPE_1__ onmatch; int /*<<< orphan*/ * params; } ;

/* Variables and functions */
 scalar_t__ action_trace ; 
 scalar_t__ onmax_save ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool actions_match(struct hist_trigger_data *hist_data,
			  struct hist_trigger_data *hist_data_test)
{
	unsigned int i, j;

	if (hist_data->n_actions != hist_data_test->n_actions)
		return false;

	for (i = 0; i < hist_data->n_actions; i++) {
		struct action_data *data = hist_data->actions[i];
		struct action_data *data_test = hist_data_test->actions[i];

		if (data->fn != data_test->fn)
			return false;

		if (data->n_params != data_test->n_params)
			return false;

		for (j = 0; j < data->n_params; j++) {
			if (strcmp(data->params[j], data_test->params[j]) != 0)
				return false;
		}

		if (data->fn == action_trace) {
			if (strcmp(data->onmatch.synth_event_name,
				   data_test->onmatch.synth_event_name) != 0)
				return false;
			if (strcmp(data->onmatch.match_event_system,
				   data_test->onmatch.match_event_system) != 0)
				return false;
			if (strcmp(data->onmatch.match_event,
				   data_test->onmatch.match_event) != 0)
				return false;
		} else if (data->fn == onmax_save) {
			if (strcmp(data->onmax.var_str,
				   data_test->onmax.var_str) != 0)
				return false;
			if (strcmp(data->onmax.fn_name,
				   data_test->onmax.fn_name) != 0)
				return false;
		}
	}

	return true;
}