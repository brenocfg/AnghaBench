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
struct module {int dummy; } ;
struct kobject {int dummy; } ;
struct cdev {int /*<<< orphan*/  kobj; struct module* owner; } ;

/* Variables and functions */
 struct kobject* kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

__attribute__((used)) static struct kobject *cdev_get(struct cdev *p)
{
	struct module *owner = p->owner;
	struct kobject *kobj;

	if (owner && !try_module_get(owner))
		return NULL;
	kobj = kobject_get(&p->kobj);
	if (!kobj)
		module_put(owner);
	return kobj;
}