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
struct klp_ops {int /*<<< orphan*/  func_stack; } ;
struct klp_func {unsigned long new_size; unsigned long old_size; scalar_t__ new_func; scalar_t__ old_func; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ KLP_UNPATCHED ; 
 struct klp_ops* klp_find_ops (scalar_t__) ; 
 scalar_t__ klp_target_state ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 struct klp_func* list_next_entry (struct klp_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_node ; 

__attribute__((used)) static int klp_check_stack_func(struct klp_func *func, unsigned long *entries,
				unsigned int nr_entries)
{
	unsigned long func_addr, func_size, address;
	struct klp_ops *ops;
	int i;

	for (i = 0; i < nr_entries; i++) {
		address = entries[i];

		if (klp_target_state == KLP_UNPATCHED) {
			 /*
			  * Check for the to-be-unpatched function
			  * (the func itself).
			  */
			func_addr = (unsigned long)func->new_func;
			func_size = func->new_size;
		} else {
			/*
			 * Check for the to-be-patched function
			 * (the previous func).
			 */
			ops = klp_find_ops(func->old_func);

			if (list_is_singular(&ops->func_stack)) {
				/* original function */
				func_addr = (unsigned long)func->old_func;
				func_size = func->old_size;
			} else {
				/* previously patched function */
				struct klp_func *prev;

				prev = list_next_entry(func, stack_node);
				func_addr = (unsigned long)prev->new_func;
				func_size = prev->new_size;
			}
		}

		if (address >= func_addr && address < func_addr + func_size)
			return -EAGAIN;
	}

	return 0;
}