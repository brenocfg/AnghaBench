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
struct hist_trigger_data {int /*<<< orphan*/  n_field_var_str; int /*<<< orphan*/  n_field_vars; struct field_var** field_vars; } ;
struct field_var {TYPE_1__* val; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int HIST_FIELD_FL_STRING ; 

__attribute__((used)) static void save_field_var(struct hist_trigger_data *hist_data,
			   struct field_var *field_var)
{
	hist_data->field_vars[hist_data->n_field_vars++] = field_var;

	if (field_var->val->flags & HIST_FIELD_FL_STRING)
		hist_data->n_field_var_str++;
}