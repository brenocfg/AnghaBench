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
struct hist_trigger_data {TYPE_2__* attrs; } ;
struct TYPE_3__ {char** name; char** expr; unsigned int n_vars; } ;
struct TYPE_4__ {unsigned int n_assignments; char** assignment_str; TYPE_1__ var_defs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int TRACING_MAP_VARS_MAX ; 
 int /*<<< orphan*/  free_var_defs (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  hist_err (char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_var_defs(struct hist_trigger_data *hist_data)
{
	char *s, *str, *var_name, *field_str;
	unsigned int i, j, n_vars = 0;
	int ret = 0;

	for (i = 0; i < hist_data->attrs->n_assignments; i++) {
		str = hist_data->attrs->assignment_str[i];
		for (j = 0; j < TRACING_MAP_VARS_MAX; j++) {
			field_str = strsep(&str, ",");
			if (!field_str)
				break;

			var_name = strsep(&field_str, "=");
			if (!var_name || !field_str) {
				hist_err("Malformed assignment: ", var_name);
				ret = -EINVAL;
				goto free;
			}

			if (n_vars == TRACING_MAP_VARS_MAX) {
				hist_err("Too many variables defined: ", var_name);
				ret = -EINVAL;
				goto free;
			}

			s = kstrdup(var_name, GFP_KERNEL);
			if (!s) {
				ret = -ENOMEM;
				goto free;
			}
			hist_data->attrs->var_defs.name[n_vars] = s;

			s = kstrdup(field_str, GFP_KERNEL);
			if (!s) {
				kfree(hist_data->attrs->var_defs.name[n_vars]);
				ret = -ENOMEM;
				goto free;
			}
			hist_data->attrs->var_defs.expr[n_vars++] = s;

			hist_data->attrs->var_defs.n_vars = n_vars;
		}
	}

	return ret;
 free:
	free_var_defs(hist_data);

	return ret;
}