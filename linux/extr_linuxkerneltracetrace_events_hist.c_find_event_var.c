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
struct trace_array {int dummy; } ;
struct hist_trigger_data {TYPE_1__* event_file; } ;
struct hist_field {int dummy; } ;
struct TYPE_2__ {struct trace_array* tr; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct hist_field*) ; 
 struct hist_field* find_file_var (struct trace_event_file*,char*) ; 
 struct hist_field* find_match_var (struct hist_trigger_data*,char*) ; 
 struct trace_event_file* find_var_file (struct trace_array*,char*,char*,char*) ; 

__attribute__((used)) static struct hist_field *find_event_var(struct hist_trigger_data *hist_data,
					 char *system,
					 char *event_name,
					 char *var_name)
{
	struct trace_array *tr = hist_data->event_file->tr;
	struct hist_field *hist_field = NULL;
	struct trace_event_file *file;

	if (!system || !event_name) {
		hist_field = find_match_var(hist_data, var_name);
		if (IS_ERR(hist_field))
			return NULL;
		if (hist_field)
			return hist_field;
	}

	file = find_var_file(tr, system, event_name, var_name);
	if (!file)
		return NULL;

	hist_field = find_file_var(file, var_name);

	return hist_field;
}