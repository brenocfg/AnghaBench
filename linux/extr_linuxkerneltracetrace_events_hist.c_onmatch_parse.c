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
struct TYPE_2__ {void* synth_event_name; void* match_event_system; void* match_event; } ;
struct action_data {TYPE_1__ onmatch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct action_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_file (struct trace_array*,char*,char*) ; 
 int /*<<< orphan*/  hist_err (char*,char*) ; 
 int /*<<< orphan*/  hist_err_event (char*,char*,char*,int /*<<< orphan*/ *) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct action_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onmatch_destroy (struct action_data*) ; 
 int parse_action_params (char*,struct action_data*) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct action_data *onmatch_parse(struct trace_array *tr, char *str)
{
	char *match_event, *match_event_system;
	char *synth_event_name, *params;
	struct action_data *data;
	int ret = -EINVAL;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return ERR_PTR(-ENOMEM);

	match_event = strsep(&str, ")");
	if (!match_event || !str) {
		hist_err("onmatch: Missing closing paren: ", match_event);
		goto free;
	}

	match_event_system = strsep(&match_event, ".");
	if (!match_event) {
		hist_err("onmatch: Missing subsystem for match event: ", match_event_system);
		goto free;
	}

	if (IS_ERR(event_file(tr, match_event_system, match_event))) {
		hist_err_event("onmatch: Invalid subsystem or event name: ",
			       match_event_system, match_event, NULL);
		goto free;
	}

	data->onmatch.match_event = kstrdup(match_event, GFP_KERNEL);
	if (!data->onmatch.match_event) {
		ret = -ENOMEM;
		goto free;
	}

	data->onmatch.match_event_system = kstrdup(match_event_system, GFP_KERNEL);
	if (!data->onmatch.match_event_system) {
		ret = -ENOMEM;
		goto free;
	}

	strsep(&str, ".");
	if (!str) {
		hist_err("onmatch: Missing . after onmatch(): ", str);
		goto free;
	}

	synth_event_name = strsep(&str, "(");
	if (!synth_event_name || !str) {
		hist_err("onmatch: Missing opening paramlist paren: ", synth_event_name);
		goto free;
	}

	data->onmatch.synth_event_name = kstrdup(synth_event_name, GFP_KERNEL);
	if (!data->onmatch.synth_event_name) {
		ret = -ENOMEM;
		goto free;
	}

	params = strsep(&str, ")");
	if (!params || !str || (str && strlen(str))) {
		hist_err("onmatch: Missing closing paramlist paren: ", params);
		goto free;
	}

	ret = parse_action_params(params, data);
	if (ret)
		goto free;
 out:
	return data;
 free:
	onmatch_destroy(data);
	data = ERR_PTR(ret);
	goto out;
}