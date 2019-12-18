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
struct trace_array {int dummy; } ;
struct TYPE_2__ {void* save_data; void* check_val; } ;
struct action_data {int use_trace_keyword; int handler; int /*<<< orphan*/  action_name; int /*<<< orphan*/  action; void* fn; TYPE_1__ track_data; } ;
typedef  enum handler_id { ____Placeholder_handler_id } handler_id ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SAVE ; 
 int /*<<< orphan*/  ACTION_SNAPSHOT ; 
 int /*<<< orphan*/  ACTION_TRACE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HANDLER_ONCHANGE ; 
 int HANDLER_ONMATCH ; 
 int HANDLER_ONMAX ; 
 int /*<<< orphan*/  HIST_ERR_ACTION_MISMATCH ; 
 int /*<<< orphan*/  HIST_ERR_ACTION_NOT_FOUND ; 
 int /*<<< orphan*/  HIST_ERR_NO_CLOSING_PAREN ; 
 int /*<<< orphan*/  HIST_ERR_NO_SAVE_PARAMS ; 
 void* action_trace ; 
 void* check_track_val_changed ; 
 void* check_track_val_max ; 
 int /*<<< orphan*/  errpos (char*) ; 
 int /*<<< orphan*/  hist_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 void* ontrack_action ; 
 int parse_action_params (struct trace_array*,char*,struct action_data*) ; 
 void* save_track_data_snapshot ; 
 void* save_track_data_vars ; 
 scalar_t__ str_has_prefix (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int action_parse(struct trace_array *tr, char *str, struct action_data *data,
			enum handler_id handler)
{
	char *action_name;
	int ret = 0;

	strsep(&str, ".");
	if (!str) {
		hist_err(tr, HIST_ERR_ACTION_NOT_FOUND, 0);
		ret = -EINVAL;
		goto out;
	}

	action_name = strsep(&str, "(");
	if (!action_name || !str) {
		hist_err(tr, HIST_ERR_ACTION_NOT_FOUND, 0);
		ret = -EINVAL;
		goto out;
	}

	if (str_has_prefix(action_name, "save")) {
		char *params = strsep(&str, ")");

		if (!params) {
			hist_err(tr, HIST_ERR_NO_SAVE_PARAMS, 0);
			ret = -EINVAL;
			goto out;
		}

		ret = parse_action_params(tr, params, data);
		if (ret)
			goto out;

		if (handler == HANDLER_ONMAX)
			data->track_data.check_val = check_track_val_max;
		else if (handler == HANDLER_ONCHANGE)
			data->track_data.check_val = check_track_val_changed;
		else {
			hist_err(tr, HIST_ERR_ACTION_MISMATCH, errpos(action_name));
			ret = -EINVAL;
			goto out;
		}

		data->track_data.save_data = save_track_data_vars;
		data->fn = ontrack_action;
		data->action = ACTION_SAVE;
	} else if (str_has_prefix(action_name, "snapshot")) {
		char *params = strsep(&str, ")");

		if (!str) {
			hist_err(tr, HIST_ERR_NO_CLOSING_PAREN, errpos(params));
			ret = -EINVAL;
			goto out;
		}

		if (handler == HANDLER_ONMAX)
			data->track_data.check_val = check_track_val_max;
		else if (handler == HANDLER_ONCHANGE)
			data->track_data.check_val = check_track_val_changed;
		else {
			hist_err(tr, HIST_ERR_ACTION_MISMATCH, errpos(action_name));
			ret = -EINVAL;
			goto out;
		}

		data->track_data.save_data = save_track_data_snapshot;
		data->fn = ontrack_action;
		data->action = ACTION_SNAPSHOT;
	} else {
		char *params = strsep(&str, ")");

		if (str_has_prefix(action_name, "trace"))
			data->use_trace_keyword = true;

		if (params) {
			ret = parse_action_params(tr, params, data);
			if (ret)
				goto out;
		}

		if (handler == HANDLER_ONMAX)
			data->track_data.check_val = check_track_val_max;
		else if (handler == HANDLER_ONCHANGE)
			data->track_data.check_val = check_track_val_changed;

		if (handler != HANDLER_ONMATCH) {
			data->track_data.save_data = action_trace;
			data->fn = ontrack_action;
		} else
			data->fn = action_trace;

		data->action = ACTION_TRACE;
	}

	data->action_name = kstrdup(action_name, GFP_KERNEL);
	if (!data->action_name) {
		ret = -ENOMEM;
		goto out;
	}

	data->handler = handler;
 out:
	return ret;
}