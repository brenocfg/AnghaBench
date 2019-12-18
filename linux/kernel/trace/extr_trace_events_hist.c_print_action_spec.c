#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_save_vars; TYPE_3__** save_vars; } ;
struct action_data {scalar_t__ action; unsigned int n_params; int /*<<< orphan*/ * params; scalar_t__ use_trace_keyword; int /*<<< orphan*/  synth_event_name; } ;
struct TYPE_6__ {TYPE_2__* var; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ var; } ;

/* Variables and functions */
 scalar_t__ ACTION_SAVE ; 
 scalar_t__ ACTION_TRACE ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void print_action_spec(struct seq_file *m,
			      struct hist_trigger_data *hist_data,
			      struct action_data *data)
{
	unsigned int i;

	if (data->action == ACTION_SAVE) {
		for (i = 0; i < hist_data->n_save_vars; i++) {
			seq_printf(m, "%s", hist_data->save_vars[i]->var->var.name);
			if (i < hist_data->n_save_vars - 1)
				seq_puts(m, ",");
		}
	} else if (data->action == ACTION_TRACE) {
		if (data->use_trace_keyword)
			seq_printf(m, "%s", data->synth_event_name);
		for (i = 0; i < data->n_params; i++) {
			if (i || data->use_trace_keyword)
				seq_puts(m, ",");
			seq_printf(m, "%s", data->params[i]);
		}
	}
}