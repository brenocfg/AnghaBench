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
struct trace_array {int dummy; } ;
struct hist_trigger_data {int /*<<< orphan*/  n_actions; struct action_data** actions; TYPE_2__* attrs; TYPE_1__* event_file; } ;
struct action_data {int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {unsigned int n_actions; char** action_str; } ;
struct TYPE_3__ {struct trace_array* tr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct action_data*) ; 
 int PTR_ERR (struct action_data*) ; 
 int /*<<< orphan*/  action_trace ; 
 struct action_data* onmatch_parse (struct trace_array*,char*) ; 
 struct action_data* onmax_parse (char*) ; 
 int /*<<< orphan*/  onmax_save ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int parse_actions(struct hist_trigger_data *hist_data)
{
	struct trace_array *tr = hist_data->event_file->tr;
	struct action_data *data;
	unsigned int i;
	int ret = 0;
	char *str;

	for (i = 0; i < hist_data->attrs->n_actions; i++) {
		str = hist_data->attrs->action_str[i];

		if (strncmp(str, "onmatch(", strlen("onmatch(")) == 0) {
			char *action_str = str + strlen("onmatch(");

			data = onmatch_parse(tr, action_str);
			if (IS_ERR(data)) {
				ret = PTR_ERR(data);
				break;
			}
			data->fn = action_trace;
		} else if (strncmp(str, "onmax(", strlen("onmax(")) == 0) {
			char *action_str = str + strlen("onmax(");

			data = onmax_parse(action_str);
			if (IS_ERR(data)) {
				ret = PTR_ERR(data);
				break;
			}
			data->fn = onmax_save;
		} else {
			ret = -EINVAL;
			break;
		}

		hist_data->actions[hist_data->n_actions++] = data;
	}

	return ret;
}