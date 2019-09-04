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
struct trace_event_file {int dummy; } ;
struct synth_event {unsigned int n_fields; int /*<<< orphan*/  ref; int /*<<< orphan*/  name; } ;
struct hist_trigger_data {unsigned int n_var_refs; } ;
struct hist_field {int dummy; } ;
struct TYPE_2__ {unsigned int var_ref_idx; struct synth_event* synth_event; int /*<<< orphan*/  synth_event_name; } ;
struct action_data {unsigned int n_params; TYPE_1__ onmatch; int /*<<< orphan*/  fn; int /*<<< orphan*/ * params; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  action_trace ; 
 scalar_t__ check_synth_field (struct synth_event*,struct hist_field*,unsigned int) ; 
 struct hist_field* create_var_ref (struct hist_field*,char*,char*) ; 
 struct synth_event* find_synth_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hist_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hist_err_event (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct hist_field* onmatch_create_field_var (struct hist_trigger_data*,struct action_data*,char*,char*,char*) ; 
 struct hist_field* onmatch_find_var (struct hist_trigger_data*,struct action_data*,char*,char*,char*) ; 
 int /*<<< orphan*/  save_synth_var_ref (struct hist_trigger_data*,struct hist_field*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  synth_event_mutex ; 

__attribute__((used)) static int onmatch_create(struct hist_trigger_data *hist_data,
			  struct trace_event_file *file,
			  struct action_data *data)
{
	char *event_name, *param, *system = NULL;
	struct hist_field *hist_field, *var_ref;
	unsigned int i, var_ref_idx;
	unsigned int field_pos = 0;
	struct synth_event *event;
	int ret = 0;

	mutex_lock(&synth_event_mutex);
	event = find_synth_event(data->onmatch.synth_event_name);
	if (!event) {
		hist_err("onmatch: Couldn't find synthetic event: ", data->onmatch.synth_event_name);
		mutex_unlock(&synth_event_mutex);
		return -EINVAL;
	}
	event->ref++;
	mutex_unlock(&synth_event_mutex);

	var_ref_idx = hist_data->n_var_refs;

	for (i = 0; i < data->n_params; i++) {
		char *p;

		p = param = kstrdup(data->params[i], GFP_KERNEL);
		if (!param) {
			ret = -ENOMEM;
			goto err;
		}

		system = strsep(&param, ".");
		if (!param) {
			param = (char *)system;
			system = event_name = NULL;
		} else {
			event_name = strsep(&param, ".");
			if (!param) {
				kfree(p);
				ret = -EINVAL;
				goto err;
			}
		}

		if (param[0] == '$')
			hist_field = onmatch_find_var(hist_data, data, system,
						      event_name, param);
		else
			hist_field = onmatch_create_field_var(hist_data, data,
							      system,
							      event_name,
							      param);

		if (!hist_field) {
			kfree(p);
			ret = -EINVAL;
			goto err;
		}

		if (check_synth_field(event, hist_field, field_pos) == 0) {
			var_ref = create_var_ref(hist_field, system, event_name);
			if (!var_ref) {
				kfree(p);
				ret = -ENOMEM;
				goto err;
			}

			save_synth_var_ref(hist_data, var_ref);
			field_pos++;
			kfree(p);
			continue;
		}

		hist_err_event("onmatch: Param type doesn't match synthetic event field type: ",
			       system, event_name, param);
		kfree(p);
		ret = -EINVAL;
		goto err;
	}

	if (field_pos != event->n_fields) {
		hist_err("onmatch: Param count doesn't match synthetic event field count: ", event->name);
		ret = -EINVAL;
		goto err;
	}

	data->fn = action_trace;
	data->onmatch.synth_event = event;
	data->onmatch.var_ref_idx = var_ref_idx;
 out:
	return ret;
 err:
	mutex_lock(&synth_event_mutex);
	event->ref--;
	mutex_unlock(&synth_event_mutex);

	goto out;
}