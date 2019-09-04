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
struct kobject {struct kernfs_node* sd; } ;
struct kernfs_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int kernfs_rename_ns (struct kernfs_node*,struct kernfs_node*,int /*<<< orphan*/ ,void const*) ; 
 struct kernfs_node* sysfs_root_kn ; 

int sysfs_move_dir_ns(struct kobject *kobj, struct kobject *new_parent_kobj,
		      const void *new_ns)
{
	struct kernfs_node *kn = kobj->sd;
	struct kernfs_node *new_parent;

	new_parent = new_parent_kobj && new_parent_kobj->sd ?
		new_parent_kobj->sd : sysfs_root_kn;

	return kernfs_rename_ns(kn, new_parent, kn->name, new_ns);
}