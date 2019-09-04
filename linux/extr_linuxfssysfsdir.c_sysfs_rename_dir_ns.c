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
 struct kernfs_node* kernfs_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int kernfs_rename_ns (int /*<<< orphan*/ ,struct kernfs_node*,char const*,void const*) ; 

int sysfs_rename_dir_ns(struct kobject *kobj, const char *new_name,
			const void *new_ns)
{
	struct kernfs_node *parent;
	int ret;

	parent = kernfs_get_parent(kobj->sd);
	ret = kernfs_rename_ns(kobj->sd, parent, new_name, new_ns);
	kernfs_put(parent);
	return ret;
}