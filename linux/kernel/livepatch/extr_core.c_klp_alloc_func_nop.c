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
struct klp_object {int dummy; } ;
struct klp_func {int nop; int /*<<< orphan*/  old_sympos; scalar_t__ old_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct klp_func*) ; 
 int /*<<< orphan*/  klp_init_func_early (struct klp_object*,struct klp_func*) ; 
 scalar_t__ kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 
 struct klp_func* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct klp_func *klp_alloc_func_nop(struct klp_func *old_func,
					   struct klp_object *obj)
{
	struct klp_func *func;

	func = kzalloc(sizeof(*func), GFP_KERNEL);
	if (!func)
		return NULL;

	if (old_func->old_name) {
		func->old_name = kstrdup(old_func->old_name, GFP_KERNEL);
		if (!func->old_name) {
			kfree(func);
			return NULL;
		}
	}

	klp_init_func_early(obj, func);
	/*
	 * func->new_func is same as func->old_func. These addresses are
	 * set when the object is loaded, see klp_init_object_loaded().
	 */
	func->old_sympos = old_func->old_sympos;
	func->nop = true;

	return func;
}