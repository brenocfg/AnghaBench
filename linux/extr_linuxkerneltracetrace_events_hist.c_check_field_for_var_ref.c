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
struct hist_trigger_data {int dummy; } ;
struct TYPE_2__ {unsigned int idx; struct hist_trigger_data* hist_data; } ;
struct hist_field {int flags; TYPE_1__ var; } ;

/* Variables and functions */
 int HIST_FIELD_FL_VAR_REF ; 

__attribute__((used)) static struct hist_field *
check_field_for_var_ref(struct hist_field *hist_field,
			struct hist_trigger_data *var_data,
			unsigned int var_idx)
{
	struct hist_field *found = NULL;

	if (hist_field && hist_field->flags & HIST_FIELD_FL_VAR_REF) {
		if (hist_field->var.idx == var_idx &&
		    hist_field->var.hist_data == var_data) {
			found = hist_field;
		}
	}

	return found;
}