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
struct overflow_data {TYPE_1__* type; int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/  old_val_str ;
struct TYPE_2__ {int /*<<< orphan*/  type_name; } ;

/* Variables and functions */
 int VALUE_LENGTH ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  val_to_string (char*,int,TYPE_1__*,void*) ; 

void __ubsan_handle_negate_overflow(struct overflow_data *data,
				void *old_val)
{
	unsigned long flags;
	char old_val_str[VALUE_LENGTH];

	if (suppress_report(&data->location))
		return;

	ubsan_prologue(&data->location, &flags);

	val_to_string(old_val_str, sizeof(old_val_str), data->type, old_val);

	pr_err("negation of %s cannot be represented in type %s:\n",
		old_val_str, data->type->type_name);

	ubsan_epilogue(&flags);
}