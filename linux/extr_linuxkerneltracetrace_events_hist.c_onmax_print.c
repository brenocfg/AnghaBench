#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char* u64 ;
struct tracing_map_elt {int dummy; } ;
struct seq_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_max_vars; TYPE_4__** max_vars; } ;
struct TYPE_10__ {unsigned int idx; int /*<<< orphan*/  name; } ;
struct hist_field {int flags; TYPE_5__ var; } ;
struct TYPE_8__ {TYPE_2__* max_var; } ;
struct action_data {TYPE_3__ onmax; } ;
struct TYPE_9__ {struct hist_field* var; struct hist_field* val; } ;
struct TYPE_6__ {unsigned int idx; } ;
struct TYPE_7__ {TYPE_1__ var; } ;

/* Variables and functions */
 int HIST_FIELD_FL_STRING ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,...) ; 
 char* tracing_map_read_var (struct tracing_map_elt*,unsigned int) ; 

__attribute__((used)) static void onmax_print(struct seq_file *m,
			struct hist_trigger_data *hist_data,
			struct tracing_map_elt *elt,
			struct action_data *data)
{
	unsigned int i, save_var_idx, max_idx = data->onmax.max_var->var.idx;

	seq_printf(m, "\n\tmax: %10llu", tracing_map_read_var(elt, max_idx));

	for (i = 0; i < hist_data->n_max_vars; i++) {
		struct hist_field *save_val = hist_data->max_vars[i]->val;
		struct hist_field *save_var = hist_data->max_vars[i]->var;
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