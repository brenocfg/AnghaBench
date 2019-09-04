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
struct hist_elt_data {struct hist_elt_data* comm; struct hist_elt_data** field_var_str; } ;

/* Variables and functions */
 unsigned int SYNTH_FIELDS_MAX ; 
 int /*<<< orphan*/  kfree (struct hist_elt_data*) ; 

__attribute__((used)) static void hist_elt_data_free(struct hist_elt_data *elt_data)
{
	unsigned int i;

	for (i = 0; i < SYNTH_FIELDS_MAX; i++)
		kfree(elt_data->field_var_str[i]);

	kfree(elt_data->comm);
	kfree(elt_data);
}