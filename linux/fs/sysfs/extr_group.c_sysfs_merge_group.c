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
struct attribute {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int ENOENT ; 
 struct kernfs_node* kernfs_find_and_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_get_ownership (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_add_file_mode_ns (struct kernfs_node*,struct attribute* const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sysfs_merge_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	struct kernfs_node *parent;
	kuid_t uid;
	kgid_t gid;
	int error = 0;
	struct attribute *const *attr;
	int i;

	parent = kernfs_find_and_get(kobj->sd, grp->name);
	if (!parent)
		return -ENOENT;

	kobject_get_ownership(kobj, &uid, &gid);

	for ((i = 0, attr = grp->attrs); *attr && !error; (++i, ++attr))
		error = sysfs_add_file_mode_ns(parent, *attr, false,
					       (*attr)->mode, uid, gid, NULL);
	if (error) {
		while (--i >= 0)
			kernfs_remove_by_name(parent, (*--attr)->name);
	}
	kernfs_put(parent);

	return error;
}