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
typedef  char* u64 ;
struct tracing_map_elt {int dummy; } ;
struct seq_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_save_vars; TYPE_1__** save_vars; } ;
struct TYPE_4__ {unsigned int idx; int /*<<< orphan*/  name; } ;
struct hist_field {int flags; TYPE_2__ var; } ;
struct action_data {scalar_t__ handler; scalar_t__ action; } ;
struct TYPE_3__ {struct hist_field* var; struct hist_field* val; } ;

/* Variables and functions */
 scalar_t__ ACTION_SNAPSHOT ; 
 scalar_t__ HANDLER_ONCHANGE ; 
 scalar_t__ HANDLER_ONMAX ; 
 int HIST_FIELD_FL_STRING ; 
 char* get_track_val (struct hist_trigger_data*,struct tracing_map_elt*,struct action_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 char* tracing_map_read_var (struct tracing_map_elt*,unsigned int) ; 

__attribute__((used)) static void track_data_print(struct seq_file *m,
			     struct hist_trigger_data *hist_data,
			     struct tracing_map_elt *elt,
			     struct action_data *data)
{
	u64 track_val = get_track_val(hist_data, elt, data);
	unsigned int i, save_var_idx;

	if (data->handler == HANDLER_ONMAX)
		seq_printf(m, "\n\tmax: %10llu", track_val);
	else if (data->handler == HANDLER_ONCHANGE)
		seq_printf(m, "\n\tchanged: %10llu", track_val);

	if (data->action == ACTION_SNAPSHOT)
		return;

	for (i = 0; i < hist_data->n_save_vars; i++) {
		struct hist_field *save_val = hist_data->save_vars[i]->val;
		struct hist_field *save_var = hist_data->save_vars[i]->var;
		u64 val;

		save_var_idx = save_var->var.idx;

		val = tracing_map_read_var(elt, save_var_idx);

		if (save_val->flags & HIST_FIELD_FL_STRING) {
			seq_printf(m, "  %s: %-32s", save_var->var.name,
				   (char *)(uintptr_t)(val));
		} else
			seq_printf(m, "  %s: %10llu", save_var->var.name, val);
	}
}