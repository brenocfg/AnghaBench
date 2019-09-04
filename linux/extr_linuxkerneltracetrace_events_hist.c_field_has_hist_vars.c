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
struct hist_field {int flags; struct hist_field** operands; } ;

/* Variables and functions */
 int HIST_FIELD_FL_VAR ; 
 int HIST_FIELD_FL_VAR_REF ; 
 int HIST_FIELD_OPERANDS_MAX ; 

__attribute__((used)) static bool field_has_hist_vars(struct hist_field *hist_field,
				unsigned int level)
{
	int i;

	if (level > 3)
		return false;

	if (!hist_field)
		return false;

	if (hist_field->flags & HIST_FIELD_FL_VAR ||
	    hist_field->flags & HIST_FIELD_FL_VAR_REF)
		return true;

	for (i = 0; i < HIST_FIELD_OPERANDS_MAX; i++) {
		struct hist_field *operand;

		operand = hist_field->operands[i];
		if (field_has_hist_vars(operand, level + 1))
			return true;
	}

	return false;
}