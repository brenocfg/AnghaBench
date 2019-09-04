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
struct kernfs_node {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct kernfs_node* kernfs_find_and_get (struct kernfs_node*,char const*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,int /*<<< orphan*/ ) ; 

void sysfs_remove_file_from_group(struct kobject *kobj,
		const struct attribute *attr, const char *group)
{
	struct kernfs_node *parent;

	if (group) {
		parent = kernfs_find_and_get(kobj->sd, group);
	} else {
		parent = kobj->sd;
		kernfs_get(parent);
	}

	if (parent) {
		kernfs_remove_by_name(parent, attr->name);
		kernfs_put(parent);
	}
}