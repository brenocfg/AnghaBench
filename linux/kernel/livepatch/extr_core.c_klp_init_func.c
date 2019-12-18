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
struct klp_object {int /*<<< orphan*/  kobj; } ;
struct klp_func {int patched; int transition; int old_sympos; int /*<<< orphan*/  old_name; int /*<<< orphan*/  kobj; int /*<<< orphan*/  stack_node; int /*<<< orphan*/  nop; int /*<<< orphan*/  new_func; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ KSYM_NAME_LEN ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int klp_init_func(struct klp_object *obj, struct klp_func *func)
{
	if (!func->old_name)
		return -EINVAL;

	/*
	 * NOPs get the address later. The patched module must be loaded,
	 * see klp_init_object_loaded().
	 */
	if (!func->new_func && !func->nop)
		return -EINVAL;

	if (strlen(func->old_name) >= KSYM_NAME_LEN)
		return -EINVAL;

	INIT_LIST_HEAD(&func->stack_node);
	func->patched = false;
	func->transition = false;

	/* The format for the sysfs directory is <function,sympos> where sympos
	 * is the nth occurrence of this symbol in kallsyms for the patched
	 * object. If the user selects 0 for old_sympos, then 1 will be used
	 * since a unique symbol will be the first occurrence.
	 */
	return kobject_add(&func->kobj, &obj->kobj, "%s,%lu",
			   func->old_name,
			   func->old_sympos ? func->old_sympos : 1);
}