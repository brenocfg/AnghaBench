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
struct synth_event {unsigned int n_fields; char* name; int /*<<< orphan*/  ref; } ;
struct hist_trigger_data {unsigned int n_var_refs; TYPE_1__* event_file; } ;
struct hist_field {int dummy; } ;
struct action_data {char* synth_event_name; char* action_name; unsigned int n_params; unsigned int var_ref_idx; struct synth_event* synth_event; int /*<<< orphan*/ * params; scalar_t__ use_trace_keyword; } ;
struct TYPE_2__ {struct trace_array* tr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HIST_ERR_SYNTH_COUNT_MISMATCH ; 
 int /*<<< orphan*/  HIST_ERR_SYNTH_EVENT_NOT_FOUND ; 
 int /*<<< orphan*/  HIST_ERR_SYNTH_TYPE_MISMATCH ; 
 scalar_t__ check_synth_field (struct synth_event*,struct hist_field*,unsigned int) ; 
 struct hist_field* create_var_ref (struct hist_trigger_data*,struct hist_field*,char*,char*) ; 
 int /*<<< orphan*/  errpos (char*) ; 
 int /*<<< orphan*/  event_mutex ; 
 struct synth_event* find_synth_event (char*) ; 
 int /*<<< orphan*/  hist_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 struct hist_field* trace_action_create_field_var (struct hist_trigger_data*,struct action_data*,char*,char*,char*) ; 
 struct hist_field* trace_action_find_var (struct hist_trigger_data*,struct action_data*,char*,char*,char*) ; 

__attribute__((used)) static int trace_action_create(struct hist_trigger_data *hist_data,
			       struct action_data *data)
{
	struct trace_array *tr = hist_data->event_file->tr;
	char *event_name, *param, *system = NULL;
	struct hist_field *hist_field, *var_ref;
	unsigned int i, var_ref_idx;
	unsigned int field_pos = 0;
	struct synth_event *event;
	char *synth_event_name;
	int ret = 0;

	lockdep_assert_held(&event_mutex);

	if (data->use_trace_keyword)
		synth_event_name = data->synth_event_name;
	else
		synth_event_name = data->action_name;

	event = find_synth_event(synth_event_name);
	if (!event) {
		hist_err(tr, HIST_ERR_SYNTH_EVENT_NOT_FOUND, errpos(synth_event_name));
		return -EINVAL;
	}

	event->ref++;

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
			hist_field = trace_action_find_var(hist_data, data,
							   system, event_name,
							   param);
		else
			hist_field = trace_action_create_field_var(hist_data,
								   data,
								   system,
								   event_name,
								   param);

		if (!hist_field) {
			kfree(p);
			ret = -EINVAL;
			goto err;
		}

		if (check_synth_field(event, hist_field, field_pos) == 0) {
			var_ref = create_var_ref(hist_data, hist_field,
						 system, event_name);
			if (!var_ref) {
				kfree(p);
				ret = -ENOMEM;
				goto err;
			}

			field_pos++;
			kfree(p);
			continue;
		}

		hist_err(tr, HIST_ERR_SYNTH_TYPE_MISMATCH, errpos(param));
		kfree(p);
		ret = -EINVAL;
		goto err;
	}

	if (field_pos != event->n_fields) {
		hist_err(tr, HIST_ERR_SYNTH_COUNT_MISMATCH, errpos(event->name));
		ret = -EINVAL;
		goto err;
	}

	data->synth_event = event;
	data->var_ref_idx = var_ref_idx;
 out:
	return ret;
 err:
	event->ref--;

	goto out;
}