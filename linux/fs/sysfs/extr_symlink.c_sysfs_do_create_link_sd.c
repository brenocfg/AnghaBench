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
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct kernfs_node* kernfs_create_link (struct kernfs_node*,char const*,struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_symlink_target_lock ; 
 int /*<<< orphan*/  sysfs_warn_dup (struct kernfs_node*,char const*) ; 

__attribute__((used)) static int sysfs_do_create_link_sd(struct kernfs_node *parent,
				   struct kobject *target_kobj,
				   const char *name, int warn)
{
	struct kernfs_node *kn, *target = NULL;

	if (WARN_ON(!name || !parent))
		return -EINVAL;

	/*
	 * We don't own @target_kobj and it may be removed at any time.
	 * Synchronize using sysfs_symlink_target_lock.  See
	 * sysfs_remove_dir() for details.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	if (target_kobj->sd) {
		target = target_kobj->sd;
		kernfs_get(target);
	}
	spin_unlock(&sysfs_symlink_target_lock);

	if (!target)
		return -ENOENT;

	kn = kernfs_create_link(parent, name, target);
	kernfs_put(target);

	if (!IS_ERR(kn))
		return 0;

	if (warn && PTR_ERR(kn) == -EEXIST)
		sysfs_warn_dup(parent, name);
	return PTR_ERR(kn);
}