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
struct hist_trigger_data {unsigned int n_var_refs; struct hist_field** var_refs; } ;
struct hist_field {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_field_for_var_ref (struct hist_field*,struct hist_trigger_data*,unsigned int) ; 

__attribute__((used)) static struct hist_field *find_var_ref(struct hist_trigger_data *hist_data,
				       struct hist_trigger_data *var_data,
				       unsigned int var_idx)
{
	struct hist_field *hist_field;
	unsigned int i;

	for (i = 0; i < hist_data->n_var_refs; i++) {
		hist_field = hist_data->var_refs[i];
		if (check_field_for_var_ref(hist_field, var_data, var_idx))
			return hist_field;
	}

	return NULL;
}