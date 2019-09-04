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
struct vla_bound_data {int /*<<< orphan*/  type; int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/  bound_str ;

/* Variables and functions */
 int VALUE_LENGTH ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  val_to_string (char*,int,int /*<<< orphan*/ ,unsigned long) ; 

void __ubsan_handle_vla_bound_not_positive(struct vla_bound_data *data,
					unsigned long bound)
{
	unsigned long flags;
	char bound_str[VALUE_LENGTH];

	if (suppress_report(&data->location))
		return;

	ubsan_prologue(&data->location, &flags);

	val_to_string(bound_str, sizeof(bound_str), data->type, bound);
	pr_err("variable length array bound value %s <= 0\n", bound_str);

	ubsan_epilogue(&flags);
}