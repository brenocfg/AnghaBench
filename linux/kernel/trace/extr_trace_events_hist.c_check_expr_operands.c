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
struct trace_array {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hist_data; } ;
struct hist_field {unsigned long flags; int /*<<< orphan*/  name; TYPE_1__ var; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIST_ERR_TIMESTAMP_MISMATCH ; 
 unsigned long HIST_FIELD_FL_ALIAS ; 
 unsigned long HIST_FIELD_FL_TIMESTAMP_USECS ; 
 unsigned long HIST_FIELD_FL_VAR_REF ; 
 struct hist_field* find_var_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hist_err (struct trace_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_expr_operands(struct trace_array *tr,
			       struct hist_field *operand1,
			       struct hist_field *operand2)
{
	unsigned long operand1_flags = operand1->flags;
	unsigned long operand2_flags = operand2->flags;

	if ((operand1_flags & HIST_FIELD_FL_VAR_REF) ||
	    (operand1_flags & HIST_FIELD_FL_ALIAS)) {
		struct hist_field *var;

		var = find_var_field(operand1->var.hist_data, operand1->name);
		if (!var)
			return -EINVAL;
		operand1_flags = var->flags;
	}

	if ((operand2_flags & HIST_FIELD_FL_VAR_REF) ||
	    (operand2_flags & HIST_FIELD_FL_ALIAS)) {
		struct hist_field *var;

		var = find_var_field(operand2->var.hist_data, operand2->name);
		if (!var)
			return -EINVAL;
		operand2_flags = var->flags;
	}

	if ((operand1_flags & HIST_FIELD_FL_TIMESTAMP_USECS) !=
	    (operand2_flags & HIST_FIELD_FL_TIMESTAMP_USECS)) {
		hist_err(tr, HIST_ERR_TIMESTAMP_MISMATCH, 0);
		return -EINVAL;
	}

	return 0;
}