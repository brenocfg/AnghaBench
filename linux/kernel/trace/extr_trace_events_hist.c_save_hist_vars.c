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
struct trace_array {int /*<<< orphan*/  hist_vars; } ;
struct hist_var_data {int /*<<< orphan*/  list; struct hist_trigger_data* hist_data; } ;
struct hist_trigger_data {TYPE_1__* event_file; } ;
struct TYPE_2__ {struct trace_array* tr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hist_var_data* find_hist_vars (struct hist_trigger_data*) ; 
 struct hist_var_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_array_put (struct trace_array*) ; 
 scalar_t__ tracing_check_open_get_tr (struct trace_array*) ; 

__attribute__((used)) static int save_hist_vars(struct hist_trigger_data *hist_data)
{
	struct trace_array *tr = hist_data->event_file->tr;
	struct hist_var_data *var_data;

	var_data = find_hist_vars(hist_data);
	if (var_data)
		return 0;

	if (tracing_check_open_get_tr(tr))
		return -ENODEV;

	var_data = kzalloc(sizeof(*var_data), GFP_KERNEL);
	if (!var_data) {
		trace_array_put(tr);
		return -ENOMEM;
	}

	var_data->hist_data = hist_data;
	list_add(&var_data->list, &tr->hist_vars);

	return 0;
}