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
struct action_data {scalar_t__ n_params; char** params; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SYNTH_FIELDS_MAX ; 
 int /*<<< orphan*/  hist_err (char*,char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 char* strstrip (char*) ; 

__attribute__((used)) static int parse_action_params(char *params, struct action_data *data)
{
	char *param, *saved_param;
	int ret = 0;

	while (params) {
		if (data->n_params >= SYNTH_FIELDS_MAX)
			goto out;

		param = strsep(&params, ",");
		if (!param) {
			ret = -EINVAL;
			goto out;
		}

		param = strstrip(param);
		if (strlen(param) < 2) {
			hist_err("Invalid action param: ", param);
			ret = -EINVAL;
			goto out;
		}

		saved_param = kstrdup(param, GFP_KERNEL);
		if (!saved_param) {
			ret = -ENOMEM;
			goto out;
		}

		data->params[data->n_params++] = saved_param;
	}
 out:
	return ret;
}