#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kernfs_node {scalar_t__ ns; struct kernfs_node* parent; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_sb; TYPE_1__ d_name; struct dentry* d_parent; } ;
struct TYPE_4__ {scalar_t__ ns; } ;

/* Variables and functions */
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  kernfs_active (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_dentry_node (struct dentry*) ; 
 TYPE_2__* kernfs_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 scalar_t__ kernfs_ns_enabled (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kernfs_dop_revalidate(struct dentry *dentry, unsigned int flags)
{
	struct kernfs_node *kn;

	if (flags & LOOKUP_RCU)
		return -ECHILD;

	/* Always perform fresh lookup for negatives */
	if (d_really_is_negative(dentry))
		goto out_bad_unlocked;

	kn = kernfs_dentry_node(dentry);
	mutex_lock(&kernfs_mutex);

	/* The kernfs node has been deactivated */
	if (!kernfs_active(kn))
		goto out_bad;

	/* The kernfs node has been moved? */
	if (kernfs_dentry_node(dentry->d_parent) != kn->parent)
		goto out_bad;

	/* The kernfs node has been renamed */
	if (strcmp(dentry->d_name.name, kn->name) != 0)
		goto out_bad;

	/* The kernfs node has been moved to a different namespace */
	if (kn->parent && kernfs_ns_enabled(kn->parent) &&
	    kernfs_info(dentry->d_sb)->ns != kn->ns)
		goto out_bad;

	mutex_unlock(&kernfs_mutex);
	return 1;
out_bad:
	mutex_unlock(&kernfs_mutex);
out_bad_unlocked:
	return 0;
}