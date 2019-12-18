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
typedef  int /*<<< orphan*/  val_str ;
struct invalid_value_data {TYPE_1__* type; int /*<<< orphan*/  location; } ;
struct TYPE_2__ {int /*<<< orphan*/  type_name; } ;

/* Variables and functions */
 int VALUE_LENGTH ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  val_to_string (char*,int,TYPE_1__*,void*) ; 

void __ubsan_handle_load_invalid_value(struct invalid_value_data *data,
				void *val)
{
	unsigned long flags;
	char val_str[VALUE_LENGTH];

	if (suppress_report(&data->location))
		return;

	ubsan_prologue(&data->location, &flags);

	val_to_string(val_str, sizeof(val_str), data->type, val);

	pr_err("load of value %s is not a valid value for type %s\n",
		val_str, data->type->type_name);

	ubsan_epilogue(&flags);
}