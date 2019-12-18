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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; } ;
struct kernfs_node {int /*<<< orphan*/  name; int /*<<< orphan*/  parent; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct kernfs_node* find_next_ancestor (struct kernfs_node*,struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_sops ; 
 struct dentry* lookup_one_len_unlocked (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

struct dentry *kernfs_node_dentry(struct kernfs_node *kn,
				  struct super_block *sb)
{
	struct dentry *dentry;
	struct kernfs_node *knparent = NULL;

	BUG_ON(sb->s_op != &kernfs_sops);

	dentry = dget(sb->s_root);

	/* Check if this is the root kernfs_node */
	if (!kn->parent)
		return dentry;

	knparent = find_next_ancestor(kn, NULL);
	if (WARN_ON(!knparent)) {
		dput(dentry);
		return ERR_PTR(-EINVAL);
	}

	do {
		struct dentry *dtmp;
		struct kernfs_node *kntmp;

		if (kn == knparent)
			return dentry;
		kntmp = find_next_ancestor(kn, knparent);
		if (WARN_ON(!kntmp)) {
			dput(dentry);
			return ERR_PTR(-EINVAL);
		}
		dtmp = lookup_one_len_unlocked(kntmp->name, dentry,
					       strlen(kntmp->name));
		dput(dentry);
		if (IS_ERR(dtmp))
			return dtmp;
		knparent = kntmp;
		dentry = dtmp;
	} while (true);
}