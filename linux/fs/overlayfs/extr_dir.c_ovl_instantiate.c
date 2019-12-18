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
struct ovl_inode_params {struct inode* newinode; struct dentry* upperdentry; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 scalar_t__ d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  ovl_dentry_set_upper_alias (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dir_modified (int /*<<< orphan*/ ,int) ; 
 struct inode* ovl_get_inode (int /*<<< orphan*/ ,struct ovl_inode_params*) ; 
 scalar_t__ ovl_inode_real (struct inode*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct dentry*) ; 

__attribute__((used)) static int ovl_instantiate(struct dentry *dentry, struct inode *inode,
			   struct dentry *newdentry, bool hardlink)
{
	struct ovl_inode_params oip = {
		.upperdentry = newdentry,
		.newinode = inode,
	};

	ovl_dir_modified(dentry->d_parent, false);
	ovl_dentry_set_upper_alias(dentry);
	if (!hardlink) {
		/*
		 * ovl_obtain_alias() can be called after ovl_create_real()
		 * and before we get here, so we may get an inode from cache
		 * with the same real upperdentry that is not the inode we
		 * pre-allocated.  In this case we will use the cached inode
		 * to instantiate the new dentry.
		 *
		 * XXX: if we ever use ovl_obtain_alias() to decode directory
		 * file handles, need to use ovl_get_inode_locked() and
		 * d_instantiate_new() here to prevent from creating two
		 * hashed directory inode aliases.
		 */
		inode = ovl_get_inode(dentry->d_sb, &oip);
		if (IS_ERR(inode))
			return PTR_ERR(inode);
	} else {
		WARN_ON(ovl_inode_real(inode) != d_inode(newdentry));
		dput(newdentry);
		inc_nlink(inode);
	}

	d_instantiate(dentry, inode);
	if (inode != oip.newinode) {
		pr_warn_ratelimited("overlayfs: newly created inode found in cache (%pd2)\n",
				    dentry);
	}

	/* Force lookup of new upper hardlink to find its lower */
	if (hardlink)
		d_drop(dentry);

	return 0;
}