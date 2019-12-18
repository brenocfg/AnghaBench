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
struct kobject {struct kobj_type* ktype; scalar_t__ state_initialized; } ;
struct kobj_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  kobject_init_internal (struct kobject*) ; 
 int /*<<< orphan*/  pr_err (char*,struct kobject*,...) ; 

void kobject_init(struct kobject *kobj, struct kobj_type *ktype)
{
	char *err_str;

	if (!kobj) {
		err_str = "invalid kobject pointer!";
		goto error;
	}
	if (!ktype) {
		err_str = "must have a ktype to be initialized properly!\n";
		goto error;
	}
	if (kobj->state_initialized) {
		/* do not error out as sometimes we can recover */
		pr_err("kobject (%p): tried to init an initialized object, something is seriously wrong.\n",
		       kobj);
		dump_stack();
	}

	kobject_init_internal(kobj);
	kobj->ktype = ktype;
	return;

error:
	pr_err("kobject (%p): %s\n", kobj, err_str);
	dump_stack();
}