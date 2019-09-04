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
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_vals; TYPE_2__* attrs; } ;
struct TYPE_3__ {unsigned int n_vars; char** name; char** expr; } ;
struct TYPE_4__ {TYPE_1__ var_defs; } ;

/* Variables and functions */
 int create_var_field (struct hist_trigger_data*,int /*<<< orphan*/ ,struct trace_event_file*,char*,char*) ; 

__attribute__((used)) static int create_var_fields(struct hist_trigger_data *hist_data,
			     struct trace_event_file *file)
{
	unsigned int i, j = hist_data->n_vals;
	int ret = 0;

	unsigned int n_vars = hist_data->attrs->var_defs.n_vars;

	for (i = 0; i < n_vars; i++) {
		char *var_name = hist_data->attrs->var_defs.name[i];
		char *expr = hist_data->attrs->var_defs.expr[i];

		ret = create_var_field(hist_data, j++, file, var_name, expr);
		if (ret)
			goto out;
	}
 out:
	return ret;
}