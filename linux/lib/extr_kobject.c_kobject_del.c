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
struct kobject {int /*<<< orphan*/ * parent; scalar_t__ state_in_sysfs; struct kernfs_node* sd; } ;
struct kobj_type {int /*<<< orphan*/  default_groups; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 struct kobj_type* get_ktype (struct kobject*) ; 
 int /*<<< orphan*/  kobj_kset_leave (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  sysfs_remove_dir (struct kobject*) ; 
 int /*<<< orphan*/  sysfs_remove_groups (struct kobject*,int /*<<< orphan*/ ) ; 

void kobject_del(struct kobject *kobj)
{
	struct kernfs_node *sd;
	const struct kobj_type *ktype;

	if (!kobj)
		return;

	sd = kobj->sd;
	ktype = get_ktype(kobj);

	if (ktype)
		sysfs_remove_groups(kobj, ktype->default_groups);

	sysfs_remove_dir(kobj);
	sysfs_put(sd);

	kobj->state_in_sysfs = 0;
	kobj_kset_leave(kobj);
	kobject_put(kobj->parent);
	kobj->parent = NULL;
}