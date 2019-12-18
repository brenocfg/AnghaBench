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
struct hist_trigger_data {int /*<<< orphan*/  map; int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_actions (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  destroy_field_var_hists (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  destroy_field_vars (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  destroy_hist_fields (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  destroy_hist_trigger_attrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  tracing_map_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_hist_data(struct hist_trigger_data *hist_data)
{
	if (!hist_data)
		return;

	destroy_hist_trigger_attrs(hist_data->attrs);
	destroy_hist_fields(hist_data);
	tracing_map_destroy(hist_data->map);

	destroy_actions(hist_data);
	destroy_field_vars(hist_data);
	destroy_field_var_hists(hist_data);

	kfree(hist_data);
}