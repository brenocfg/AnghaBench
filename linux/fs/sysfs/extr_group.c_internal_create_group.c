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
struct kobject {struct kernfs_node* sd; int /*<<< orphan*/  name; } ;
struct kernfs_node {int dummy; } ;
struct attribute_group {scalar_t__ name; int /*<<< orphan*/  bin_attrs; int /*<<< orphan*/  attrs; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 int S_IRUGO ; 
 int S_IRWXU ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 int create_files (struct kernfs_node*,struct kobject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct attribute_group const*,int) ; 
 struct kernfs_node* kernfs_create_dir_ns (struct kernfs_node*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kobject*,int /*<<< orphan*/ *) ; 
 struct kernfs_node* kernfs_find_and_get (struct kernfs_node*,scalar_t__) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove (struct kernfs_node*) ; 
 int /*<<< orphan*/  kobject_get_ownership (struct kobject*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sysfs_warn_dup (struct kernfs_node*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int internal_create_group(struct kobject *kobj, int update,
				 const struct attribute_group *grp)
{
	struct kernfs_node *kn;
	kuid_t uid;
	kgid_t gid;
	int error;

	if (WARN_ON(!kobj || (!update && !kobj->sd)))
		return -EINVAL;

	/* Updates may happen before the object has been instantiated */
	if (unlikely(update && !kobj->sd))
		return -EINVAL;
	if (!grp->attrs && !grp->bin_attrs) {
		WARN(1, "sysfs: (bin_)attrs not set by subsystem for group: %s/%s\n",
			kobj->name, grp->name ?: "");
		return -EINVAL;
	}
	kobject_get_ownership(kobj, &uid, &gid);
	if (grp->name) {
		if (update) {
			kn = kernfs_find_and_get(kobj->sd, grp->name);
			if (!kn) {
				pr_warn("Can't update unknown attr grp name: %s/%s\n",
					kobj->name, grp->name);
				return -EINVAL;
			}
		} else {
			kn = kernfs_create_dir_ns(kobj->sd, grp->name,
						  S_IRWXU | S_IRUGO | S_IXUGO,
						  uid, gid, kobj, NULL);
			if (IS_ERR(kn)) {
				if (PTR_ERR(kn) == -EEXIST)
					sysfs_warn_dup(kobj->sd, grp->name);
				return PTR_ERR(kn);
			}
		}
	} else
		kn = kobj->sd;
	kernfs_get(kn);
	error = create_files(kn, kobj, uid, gid, grp, update);
	if (error) {
		if (grp->name)
			kernfs_remove(kn);
	}
	kernfs_put(kn);

	if (grp->name && update)
		kernfs_put(kn);

	return error;
}