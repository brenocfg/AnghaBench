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
struct kobject {int /*<<< orphan*/  sd; } ;
struct kernfs_node {int dummy; } ;
struct attribute_group {struct attribute** attrs; int /*<<< orphan*/  name; } ;
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct kernfs_node* kernfs_find_and_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,int /*<<< orphan*/ ) ; 

void sysfs_unmerge_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	struct kernfs_node *parent;
	struct attribute *const *attr;

	parent = kernfs_find_and_get(kobj->sd, grp->name);
	if (parent) {
		for (attr = grp->attrs; *attr; ++attr)
			kernfs_remove_by_name(parent, (*attr)->name);
		kernfs_put(parent);
	}
}