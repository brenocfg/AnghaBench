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
typedef  int /*<<< orphan*/  va_list ;
struct kobject {struct kobject* parent; } ;

/* Variables and functions */
 int kobject_add_internal (struct kobject*) ; 
 int kobject_set_name_vargs (struct kobject*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int kobject_add_varg(struct kobject *kobj,
					   struct kobject *parent,
					   const char *fmt, va_list vargs)
{
	int retval;

	retval = kobject_set_name_vargs(kobj, fmt, vargs);
	if (retval) {
		pr_err("kobject: can not set name properly!\n");
		return retval;
	}
	kobj->parent = parent;
	return kobject_add_internal(kobj);
}