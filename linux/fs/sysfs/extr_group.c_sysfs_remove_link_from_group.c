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

/* Variables and functions */
 struct kernfs_node* kernfs_find_and_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,char const*) ; 

void sysfs_remove_link_from_group(struct kobject *kobj, const char *group_name,
				  const char *link_name)
{
	struct kernfs_node *parent;

	parent = kernfs_find_and_get(kobj->sd, group_name);
	if (parent) {
		kernfs_remove_by_name(parent, link_name);
		kernfs_put(parent);
	}
}