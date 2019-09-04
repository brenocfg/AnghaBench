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

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_create_empty_dir (struct kernfs_node*,char const*) ; 
 int /*<<< orphan*/  sysfs_warn_dup (struct kernfs_node*,char const*) ; 

int sysfs_create_mount_point(struct kobject *parent_kobj, const char *name)
{
	struct kernfs_node *kn, *parent = parent_kobj->sd;

	kn = kernfs_create_empty_dir(parent, name);
	if (IS_ERR(kn)) {
		if (PTR_ERR(kn) == -EEXIST)
			sysfs_warn_dup(parent, name);
		return PTR_ERR(kn);
	}

	return 0;
}