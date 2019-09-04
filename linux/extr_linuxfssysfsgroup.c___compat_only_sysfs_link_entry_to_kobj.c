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
 int /*<<< orphan*/  EEXIST ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int /*<<< orphan*/  PTR_ERR (struct kernfs_node*) ; 
 int PTR_ERR_OR_ZERO (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_create_link (struct kernfs_node*,char const*,struct kernfs_node*) ; 
 struct kernfs_node* kernfs_find_and_get (struct kernfs_node*,char const*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_symlink_target_lock ; 
 int /*<<< orphan*/  sysfs_warn_dup (struct kernfs_node*,char const*) ; 

int __compat_only_sysfs_link_entry_to_kobj(struct kobject *kobj,
				      struct kobject *target_kobj,
				      const char *target_name)
{
	struct kernfs_node *target;
	struct kernfs_node *entry;
	struct kernfs_node *link;

	/*
	 * We don't own @target_kobj and it may be removed at any time.
	 * Synchronize using sysfs_symlink_target_lock. See sysfs_remove_dir()
	 * for details.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	target = target_kobj->sd;
	if (target)
		kernfs_get(target);
	spin_unlock(&sysfs_symlink_target_lock);
	if (!target)
		return -ENOENT;

	entry = kernfs_find_and_get(target_kobj->sd, target_name);
	if (!entry) {
		kernfs_put(target);
		return -ENOENT;
	}

	link = kernfs_create_link(kobj->sd, target_name, entry);
	if (IS_ERR(link) && PTR_ERR(link) == -EEXIST)
		sysfs_warn_dup(kobj->sd, target_name);

	kernfs_put(entry);
	kernfs_put(target);
	return PTR_ERR_OR_ZERO(link);
}