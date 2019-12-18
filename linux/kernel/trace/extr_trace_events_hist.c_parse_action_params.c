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
struct trace_array {int dummy; } ;
struct action_data {scalar_t__ n_params; char* synth_event_name; char** params; scalar_t__ use_trace_keyword; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIST_ERR_INVALID_PARAM ; 
 int /*<<< orphan*/  HIST_ERR_PARAM_NOT_FOUND ; 
 int /*<<< orphan*/  HIST_ERR_TOO_MANY_PARAMS ; 
 scalar_t__ SYNTH_FIELDS_MAX ; 
 int /*<<< orphan*/  errpos (char*) ; 
 int /*<<< orphan*/  hist_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static int parse_action_params(struct trace_array *tr, char *params,
			       struct action_data *data)
{
	char *param, *saved_param;
	bool first_param = true;
	int ret = 0;

	while (params) {
		if (data->n_params >= SYNTH_FIELDS_MAX) {
			hist_err(tr, HIST_ERR_TOO_MANY_PARAMS, 0);
			goto out;
		}

		param = strsep(&params, ",");
		if (!param) {
			hist_err(tr, HIST_ERR_PARAM_NOT_FOUND, 0);
			ret = -EINVAL;
			goto out;
		}

		param = strstrip(param);
		if (strlen(param) < 2) {
			hist_err(tr, HIST_ERR_INVALID_PARAM, errpos(param));
			ret = -EINVAL;
			goto out;
		}

		saved_param = kstrdup(param, GFP_KERNEL);
		if (!saved_param) {
			ret = -ENOMEM;
			goto out;
		}

		if (first_param && data->use_trace_keyword) {
			data->synth_event_name = saved_param;
			first_param = false;
			continue;
		}
		first_param = false;

		data->params[data->n_params++] = saved_param;
	}
 out:
	return ret;
}