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
struct type_descriptor {int /*<<< orphan*/  type_name; } ;
struct overflow_data {int /*<<< orphan*/  location; struct type_descriptor* type; } ;
typedef  int /*<<< orphan*/  rhs_val_str ;
typedef  int /*<<< orphan*/  lhs_val_str ;

/* Variables and functions */
 int VALUE_LENGTH ; 
 int /*<<< orphan*/  pr_err (char*,char*,...) ; 
 scalar_t__ suppress_report (int /*<<< orphan*/ *) ; 
 scalar_t__ type_is_signed (struct type_descriptor*) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  val_to_string (char*,int,struct type_descriptor*,void*) ; 

__attribute__((used)) static void handle_overflow(struct overflow_data *data, void *lhs,
			void *rhs, char op)
{

	struct type_descriptor *type = data->type;
	unsigned long flags;
	char lhs_val_str[VALUE_LENGTH];
	char rhs_val_str[VALUE_LENGTH];

	if (suppress_report(&data->location))
		return;

	ubsan_prologue(&data->location, &flags);

	val_to_string(lhs_val_str, sizeof(lhs_val_str), type, lhs);
	val_to_string(rhs_val_str, sizeof(rhs_val_str), type, rhs);
	pr_err("%s integer overflow:\n",
		type_is_signed(type) ? "signed" : "unsigned");
	pr_err("%s %c %s cannot be represented in type %s\n",
		lhs_val_str,
		op,
		rhs_val_str,
		type->type_name);

	ubsan_epilogue(&flags);
}