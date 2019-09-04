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
struct TYPE_2__ {void* fn_name; void* var_str; } ;
struct action_data {TYPE_1__ onmax; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct action_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct action_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onmax_destroy (struct action_data*) ; 
 int parse_action_params (char*,struct action_data*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct action_data *onmax_parse(char *str)
{
	char *onmax_fn_name, *onmax_var_str;
	struct action_data *data;
	int ret = -EINVAL;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return ERR_PTR(-ENOMEM);

	onmax_var_str = strsep(&str, ")");
	if (!onmax_var_str || !str) {
		ret = -EINVAL;
		goto free;
	}

	data->onmax.var_str = kstrdup(onmax_var_str, GFP_KERNEL);
	if (!data->onmax.var_str) {
		ret = -ENOMEM;
		goto free;
	}

	strsep(&str, ".");
	if (!str)
		goto free;

	onmax_fn_name = strsep(&str, "(");
	if (!onmax_fn_name || !str)
		goto free;

	if (strncmp(onmax_fn_name, "save", strlen("save")) == 0) {
		char *params = strsep(&str, ")");

		if (!params) {
			ret = -EINVAL;
			goto free;
		}

		ret = parse_action_params(params, data);
		if (ret)
			goto free;
	} else
		goto free;

	data->onmax.fn_name = kstrdup(onmax_fn_name, GFP_KERNEL);
	if (!data->onmax.fn_name) {
		ret = -ENOMEM;
		goto free;
	}
 out:
	return data;
 free:
	onmax_destroy(data);
	data = ERR_PTR(ret);
	goto out;
}