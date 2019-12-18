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
struct trace_event_file {int dummy; } ;
struct hist_trigger_data {int dummy; } ;

/* Variables and functions */
 int create_key_fields (struct hist_trigger_data*,struct trace_event_file*) ; 
 int create_val_fields (struct hist_trigger_data*,struct trace_event_file*) ; 
 int create_var_fields (struct hist_trigger_data*,struct trace_event_file*) ; 
 int /*<<< orphan*/  free_var_defs (struct hist_trigger_data*) ; 
 int parse_var_defs (struct hist_trigger_data*) ; 

__attribute__((used)) static int create_hist_fields(struct hist_trigger_data *hist_data,
			      struct trace_event_file *file)
{
	int ret;

	ret = parse_var_defs(hist_data);
	if (ret)
		goto out;

	ret = create_val_fields(hist_data, file);
	if (ret)
		goto out;

	ret = create_var_fields(hist_data, file);
	if (ret)
		goto out;

	ret = create_key_fields(hist_data, file);
	if (ret)
		goto out;
 out:
	free_var_defs(hist_data);

	return ret;
}