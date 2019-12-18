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
struct kernfs_root {int /*<<< orphan*/  ino_idr; } ;
struct TYPE_4__ {int /*<<< orphan*/  ino; } ;
struct TYPE_3__ {struct kernfs_node* target_kn; } ;
struct kernfs_node {char* name; int /*<<< orphan*/  count; TYPE_2__ id; struct kernfs_node* iattr; int /*<<< orphan*/  xattrs; TYPE_1__ symlink; int /*<<< orphan*/  active; struct kernfs_node* parent; } ;

/* Variables and functions */
 scalar_t__ KERNFS_LINK ; 
 scalar_t__ KN_DEACTIVATED_BIAS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,char*,char*,scalar_t__) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_iattrs_cache ; 
 int /*<<< orphan*/  kernfs_idr_lock ; 
 int /*<<< orphan*/  kernfs_node_cache ; 
 struct kernfs_root* kernfs_root (struct kernfs_node*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  kfree (struct kernfs_root*) ; 
 int /*<<< orphan*/  kfree_const (char*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kernfs_node*) ; 
 int /*<<< orphan*/  simple_xattrs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kernfs_put(struct kernfs_node *kn)
{
	struct kernfs_node *parent;
	struct kernfs_root *root;

	/*
	 * kernfs_node is freed with ->count 0, kernfs_find_and_get_node_by_ino
	 * depends on this to filter reused stale node
	 */
	if (!kn || !atomic_dec_and_test(&kn->count))
		return;
	root = kernfs_root(kn);
 repeat:
	/*
	 * Moving/renaming is always done while holding reference.
	 * kn->parent won't change beneath us.
	 */
	parent = kn->parent;

	WARN_ONCE(atomic_read(&kn->active) != KN_DEACTIVATED_BIAS,
		  "kernfs_put: %s/%s: released with incorrect active_ref %d\n",
		  parent ? parent->name : "", kn->name, atomic_read(&kn->active));

	if (kernfs_type(kn) == KERNFS_LINK)
		kernfs_put(kn->symlink.target_kn);

	kfree_const(kn->name);

	if (kn->iattr) {
		simple_xattrs_free(&kn->iattr->xattrs);
		kmem_cache_free(kernfs_iattrs_cache, kn->iattr);
	}
	spin_lock(&kernfs_idr_lock);
	idr_remove(&root->ino_idr, kn->id.ino);
	spin_unlock(&kernfs_idr_lock);
	kmem_cache_free(kernfs_node_cache, kn);

	kn = parent;
	if (kn) {
		if (atomic_dec_and_test(&kn->count))
			goto repeat;
	} else {
		/* just released the root kn, free @root too */
		idr_destroy(&root->ino_idr);
		kfree(root);
	}
}