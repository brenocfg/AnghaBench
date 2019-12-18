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
struct out_of_bounds_data {TYPE_1__* array_type; int /*<<< orphan*/  index_type; int /*<<< orphan*/  location; } ;
typedef  int /*<<< orphan*/  index_str ;
struct TYPE_2__ {int /*<<< orphan*/  type_name; } ;

/* Variables and functions */
 int VALUE_LENGTH ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  val_to_string (char*,int,int /*<<< orphan*/ ,void*) ; 

void __ubsan_handle_out_of_bounds(struct out_of_bounds_data *data, void *index)
{
	unsigned long flags;
	char index_str[VALUE_LENGTH];

	if (suppress_report(&data->location))
		return;

	ubsan_prologue(&data->location, &flags);

	val_to_string(index_str, sizeof(index_str), data->index_type, index);
	pr_err("index %s is out of range for type %s\n", index_str,
		data->array_type->type_name);
	ubsan_epilogue(&flags);
}