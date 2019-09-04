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
struct hist_trigger_data {size_t n_var_refs; struct hist_field** var_refs; int /*<<< orphan*/  n_synth_var_refs; struct hist_field** synth_var_refs; } ;
struct hist_field {int /*<<< orphan*/  var_ref_idx; } ;

/* Variables and functions */

__attribute__((used)) static void save_synth_var_ref(struct hist_trigger_data *hist_data,
			 struct hist_field *var_ref)
{
	hist_data->synth_var_refs[hist_data->n_synth_var_refs++] = var_ref;

	hist_data->var_refs[hist_data->n_var_refs] = var_ref;
	var_ref->var_ref_idx = hist_data->n_var_refs++;
}