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
struct trace_event_call {TYPE_2__* class; } ;
struct hist_trigger_data {TYPE_1__* event_file; } ;
struct TYPE_4__ {int /*<<< orphan*/  system; } ;
struct TYPE_3__ {struct trace_event_call* event_call; } ;

/* Variables and functions */
 char* field_name_from_var (struct hist_trigger_data*,char*) ; 
 int /*<<< orphan*/  is_var_ref (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_event_name (struct trace_event_call*) ; 

__attribute__((used)) static char *local_field_var_ref(struct hist_trigger_data *hist_data,
				 char *system, char *event_name,
				 char *var_name)
{
	struct trace_event_call *call;

	if (system && event_name) {
		call = hist_data->event_file->event_call;

		if (strcmp(system, call->class->system) != 0)
			return NULL;

		if (strcmp(event_name, trace_event_name(call)) != 0)
			return NULL;
	}

	if (!!system != !!event_name)
		return NULL;

	if (!is_var_ref(var_name))
		return NULL;

	var_name++;

	return field_name_from_var(hist_data, var_name);
}