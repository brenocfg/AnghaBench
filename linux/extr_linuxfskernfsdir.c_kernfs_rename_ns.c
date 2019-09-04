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
struct kernfs_node {int flags; void const* ns; char* name; int /*<<< orphan*/  hash; struct kernfs_node* parent; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KERNFS_EMPTY_DIR ; 
 int /*<<< orphan*/  kernfs_active (struct kernfs_node*) ; 
 scalar_t__ kernfs_find_ns (struct kernfs_node*,char const*,void const*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_link_sibling (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  kernfs_name_hash (char const*,void const*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_rename_lock ; 
 int /*<<< orphan*/  kernfs_unlink_sibling (struct kernfs_node*) ; 
 int /*<<< orphan*/  kfree_const (char const*) ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 

int kernfs_rename_ns(struct kernfs_node *kn, struct kernfs_node *new_parent,
		     const char *new_name, const void *new_ns)
{
	struct kernfs_node *old_parent;
	const char *old_name = NULL;
	int error;

	/* can't move or rename root */
	if (!kn->parent)
		return -EINVAL;

	mutex_lock(&kernfs_mutex);

	error = -ENOENT;
	if (!kernfs_active(kn) || !kernfs_active(new_parent) ||
	    (new_parent->flags & KERNFS_EMPTY_DIR))
		goto out;

	error = 0;
	if ((kn->parent == new_parent) && (kn->ns == new_ns) &&
	    (strcmp(kn->name, new_name) == 0))
		goto out;	/* nothing to rename */

	error = -EEXIST;
	if (kernfs_find_ns(new_parent, new_name, new_ns))
		goto out;

	/* rename kernfs_node */
	if (strcmp(kn->name, new_name) != 0) {
		error = -ENOMEM;
		new_name = kstrdup_const(new_name, GFP_KERNEL);
		if (!new_name)
			goto out;
	} else {
		new_name = NULL;
	}

	/*
	 * Move to the appropriate place in the appropriate directories rbtree.
	 */
	kernfs_unlink_sibling(kn);
	kernfs_get(new_parent);

	/* rename_lock protects ->parent and ->name accessors */
	spin_lock_irq(&kernfs_rename_lock);

	old_parent = kn->parent;
	kn->parent = new_parent;

	kn->ns = new_ns;
	if (new_name) {
		old_name = kn->name;
		kn->name = new_name;
	}

	spin_unlock_irq(&kernfs_rename_lock);

	kn->hash = kernfs_name_hash(kn->name, kn->ns);
	kernfs_link_sibling(kn);

	kernfs_put(old_parent);
	kfree_const(old_name);

	error = 0;
 out:
	mutex_unlock(&kernfs_mutex);
	return error;
}