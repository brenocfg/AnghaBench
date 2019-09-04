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
struct hist_trigger_data {int dummy; } ;
struct hist_field {struct hist_field** operands; } ;

/* Variables and functions */
 unsigned int HIST_FIELD_OPERANDS_MAX ; 
 struct hist_field* check_field_for_var_ref (struct hist_field*,struct hist_trigger_data*,unsigned int) ; 

__attribute__((used)) static struct hist_field *
check_field_for_var_refs(struct hist_trigger_data *hist_data,
			 struct hist_field *hist_field,
			 struct hist_trigger_data *var_data,
			 unsigned int var_idx,
			 unsigned int level)
{
	struct hist_field *found = NULL;
	unsigned int i;

	if (level > 3)
		return found;

	if (!hist_field)
		return found;

	found = check_field_for_var_ref(hist_field, var_data, var_idx);
	if (found)
		return found;

	for (i = 0; i < HIST_FIELD_OPERANDS_MAX; i++) {
		struct hist_field *operand;

		operand = hist_field->operands[i];
		found = check_field_for_var_refs(hist_data, operand, var_data,
						 var_idx, level + 1);
		if (found)
			return found;
	}

	return found;
}