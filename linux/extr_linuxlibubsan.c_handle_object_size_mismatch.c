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
struct type_mismatch_data_common {size_t type_check_kind; TYPE_1__* type; int /*<<< orphan*/  location; } ;
struct TYPE_2__ {int /*<<< orphan*/  type_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * type_check_kinds ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void handle_object_size_mismatch(struct type_mismatch_data_common *data,
					unsigned long ptr)
{
	unsigned long flags;

	if (suppress_report(data->location))
		return;

	ubsan_prologue(data->location, &flags);
	pr_err("%s address %p with insufficient space\n",
		type_check_kinds[data->type_check_kind],
		(void *) ptr);
	pr_err("for an object of type %s\n", data->type->type_name);
	ubsan_epilogue(&flags);
}