#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct overflow_data {TYPE_1__* type; int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/  rhs_val_str ;
struct TYPE_4__ {int /*<<< orphan*/  type_name; } ;

/* Variables and functions */
 int VALUE_LENGTH ; 
 int get_signed_val (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ *) ; 
 scalar_t__ type_is_signed (TYPE_1__*) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  val_to_string (char*,int,TYPE_1__*,void*) ; 

void __ubsan_handle_divrem_overflow(struct overflow_data *data,
				void *lhs, void *rhs)
{
	unsigned long flags;
	char rhs_val_str[VALUE_LENGTH];

	if (suppress_report(&data->location))
		return;

	ubsan_prologue(&data->location, &flags);

	val_to_string(rhs_val_str, sizeof(rhs_val_str), data->type, rhs);

	if (type_is_signed(data->type) && get_signed_val(data->type, rhs) == -1)
		pr_err("division of %s by -1 cannot be represented in type %s\n",
			rhs_val_str, data->type->type_name);
	else
		pr_err("division by zero\n");

	ubsan_epilogue(&flags);
}