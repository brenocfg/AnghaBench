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
struct attribute {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int ENOENT ; 
 struct kernfs_node* kernfs_find_and_get (struct kernfs_node*,char const*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kobject_get_ownership (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_add_file_mode_ns (struct kernfs_node*,struct attribute const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sysfs_add_file_to_group(struct kobject *kobj,
		const struct attribute *attr, const char *group)
{
	struct kernfs_node *parent;
	kuid_t uid;
	kgid_t gid;
	int error;

	if (group) {
		parent = kernfs_find_and_get(kobj->sd, group);
	} else {
		parent = kobj->sd;
		kernfs_get(parent);
	}

	if (!parent)
		return -ENOENT;

	kobject_get_ownership(kobj, &uid, &gid);
	error = sysfs_add_file_mode_ns(parent, attr, false,
				       attr->mode, uid, gid, NULL);
	kernfs_put(parent);

	return error;
}