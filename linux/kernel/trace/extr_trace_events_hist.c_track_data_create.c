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
typedef  int /*<<< orphan*/  u64 ;
struct trace_event_file {struct trace_array* tr; } ;
struct trace_array {int dummy; } ;
struct hist_trigger_data {struct trace_event_file* event_file; } ;
struct hist_field {int dummy; } ;
struct TYPE_2__ {char* var_str; struct hist_field* track_var; struct hist_field* var_ref; } ;
struct action_data {scalar_t__ handler; TYPE_1__ track_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ HANDLER_ONCHANGE ; 
 scalar_t__ HANDLER_ONMAX ; 
 int /*<<< orphan*/  HIST_ERR_ONX_NOT_VAR ; 
 int /*<<< orphan*/  HIST_ERR_ONX_VAR_CREATE_FAIL ; 
 int /*<<< orphan*/  HIST_ERR_ONX_VAR_NOT_FOUND ; 
 scalar_t__ IS_ERR (struct hist_field*) ; 
 int PTR_ERR (struct hist_field*) ; 
 int action_create (struct hist_trigger_data*,struct action_data*) ; 
 struct hist_field* create_var (struct hist_trigger_data*,struct trace_event_file*,char*,int,char*) ; 
 struct hist_field* create_var_ref (struct hist_trigger_data*,struct hist_field*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errpos (char*) ; 
 struct hist_field* find_target_event_var (struct hist_trigger_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hist_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int track_data_create(struct hist_trigger_data *hist_data,
			     struct action_data *data)
{
	struct hist_field *var_field, *ref_field, *track_var = NULL;
	struct trace_event_file *file = hist_data->event_file;
	struct trace_array *tr = file->tr;
	char *track_data_var_str;
	int ret = 0;

	track_data_var_str = data->track_data.var_str;
	if (track_data_var_str[0] != '$') {
		hist_err(tr, HIST_ERR_ONX_NOT_VAR, errpos(track_data_var_str));
		return -EINVAL;
	}
	track_data_var_str++;

	var_field = find_target_event_var(hist_data, NULL, NULL, track_data_var_str);
	if (!var_field) {
		hist_err(tr, HIST_ERR_ONX_VAR_NOT_FOUND, errpos(track_data_var_str));
		return -EINVAL;
	}

	ref_field = create_var_ref(hist_data, var_field, NULL, NULL);
	if (!ref_field)
		return -ENOMEM;

	data->track_data.var_ref = ref_field;

	if (data->handler == HANDLER_ONMAX)
		track_var = create_var(hist_data, file, "__max", sizeof(u64), "u64");
	if (IS_ERR(track_var)) {
		hist_err(tr, HIST_ERR_ONX_VAR_CREATE_FAIL, 0);
		ret = PTR_ERR(track_var);
		goto out;
	}

	if (data->handler == HANDLER_ONCHANGE)
		track_var = create_var(hist_data, file, "__change", sizeof(u64), "u64");
	if (IS_ERR(track_var)) {
		hist_err(tr, HIST_ERR_ONX_VAR_CREATE_FAIL, 0);
		ret = PTR_ERR(track_var);
		goto out;
	}
	data->track_data.track_var = track_var;

	ret = action_create(hist_data, data);
 out:
	return ret;
}