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
typedef  int /*<<< orphan*/  u64 ;
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {unsigned int n_var_refs; int /*<<< orphan*/  n_max_var_str; int /*<<< orphan*/  n_max_vars; struct hist_field** max_vars; struct hist_field** var_refs; struct trace_event_file* event_file; } ;
struct hist_field {TYPE_2__* val; int /*<<< orphan*/  var_ref_idx; } ;
struct field_var {TYPE_2__* val; int /*<<< orphan*/  var_ref_idx; } ;
struct TYPE_3__ {char* var_str; unsigned int max_var_ref_idx; struct hist_field* max_var; struct hist_field* var; } ;
struct action_data {unsigned int n_params; int /*<<< orphan*/ * params; TYPE_1__ onmax; int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIST_FIELD_FL_STRING ; 
 unsigned long HIST_FIELD_FL_VAR_REF ; 
 scalar_t__ IS_ERR (struct hist_field*) ; 
 int PTR_ERR (struct hist_field*) ; 
 struct hist_field* create_hist_field (struct hist_trigger_data*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 struct hist_field* create_target_field_var (struct hist_trigger_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct hist_field* create_var (struct hist_trigger_data*,struct trace_event_file*,char*,int,char*) ; 
 int /*<<< orphan*/  destroy_hist_field (struct hist_field*,int /*<<< orphan*/ ) ; 
 struct hist_field* find_target_event_var (struct hist_trigger_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hist_err (char*,char*) ; 
 scalar_t__ init_var_ref (struct hist_field*,struct hist_field*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onmax_save ; 

__attribute__((used)) static int onmax_create(struct hist_trigger_data *hist_data,
			struct action_data *data)
{
	struct trace_event_file *file = hist_data->event_file;
	struct hist_field *var_field, *ref_field, *max_var;
	unsigned int var_ref_idx = hist_data->n_var_refs;
	struct field_var *field_var;
	char *onmax_var_str, *param;
	unsigned long flags;
	unsigned int i;
	int ret = 0;

	onmax_var_str = data->onmax.var_str;
	if (onmax_var_str[0] != '$') {
		hist_err("onmax: For onmax(x), x must be a variable: ", onmax_var_str);
		return -EINVAL;
	}
	onmax_var_str++;

	var_field = find_target_event_var(hist_data, NULL, NULL, onmax_var_str);
	if (!var_field) {
		hist_err("onmax: Couldn't find onmax variable: ", onmax_var_str);
		return -EINVAL;
	}

	flags = HIST_FIELD_FL_VAR_REF;
	ref_field = create_hist_field(hist_data, NULL, flags, NULL);
	if (!ref_field)
		return -ENOMEM;

	if (init_var_ref(ref_field, var_field, NULL, NULL)) {
		destroy_hist_field(ref_field, 0);
		ret = -ENOMEM;
		goto out;
	}
	hist_data->var_refs[hist_data->n_var_refs] = ref_field;
	ref_field->var_ref_idx = hist_data->n_var_refs++;
	data->onmax.var = ref_field;

	data->fn = onmax_save;
	data->onmax.max_var_ref_idx = var_ref_idx;
	max_var = create_var(hist_data, file, "max", sizeof(u64), "u64");
	if (IS_ERR(max_var)) {
		hist_err("onmax: Couldn't create onmax variable: ", "max");
		ret = PTR_ERR(max_var);
		goto out;
	}
	data->onmax.max_var = max_var;

	for (i = 0; i < data->n_params; i++) {
		param = kstrdup(data->params[i], GFP_KERNEL);
		if (!param) {
			ret = -ENOMEM;
			goto out;
		}

		field_var = create_target_field_var(hist_data, NULL, NULL, param);
		if (IS_ERR(field_var)) {
			hist_err("onmax: Couldn't create field variable: ", param);
			ret = PTR_ERR(field_var);
			kfree(param);
			goto out;
		}

		hist_data->max_vars[hist_data->n_max_vars++] = field_var;
		if (field_var->val->flags & HIST_FIELD_FL_STRING)
			hist_data->n_max_var_str++;

		kfree(param);
	}
 out:
	return ret;
}