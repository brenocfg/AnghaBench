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
 scalar_t__ KERNFS_DIR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kernfs_remove (struct kernfs_node*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_symlink_target_lock ; 

void sysfs_remove_dir(struct kobject *kobj)
{
	struct kernfs_node *kn = kobj->sd;

	/*
	 * In general, kboject owner is responsible for ensuring removal
	 * doesn't race with other operations and sysfs doesn't provide any
	 * protection; however, when @kobj is used as a symlink target, the
	 * symlinking entity usually doesn't own @kobj and thus has no
	 * control over removal.  @kobj->sd may be removed anytime
	 * and symlink code may end up dereferencing an already freed node.
	 *
	 * sysfs_symlink_target_lock synchronizes @kobj->sd
	 * disassociation against symlink operations so that symlink code
	 * can safely dereference @kobj->sd.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	kobj->sd = NULL;
	spin_unlock(&sysfs_symlink_target_lock);

	if (kn) {
		WARN_ON_ONCE(kernfs_type(kn) != KERNFS_DIR);
		kernfs_remove(kn);
	}
}