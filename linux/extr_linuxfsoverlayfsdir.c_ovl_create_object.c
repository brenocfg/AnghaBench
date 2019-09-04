#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ovl_cattr {char const* link; int /*<<< orphan*/  mode; int /*<<< orphan*/  rdev; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_state; } ;
struct dentry {TYPE_1__* d_parent; int /*<<< orphan*/  d_sb; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  I_CREATING ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int ovl_create_or_link (struct dentry*,struct inode*,struct ovl_cattr*,int) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 struct inode* ovl_new_inode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ovl_want_write (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_create_object(struct dentry *dentry, int mode, dev_t rdev,
			     const char *link)
{
	int err;
	struct inode *inode;
	struct ovl_cattr attr = {
		.rdev = rdev,
		.link = link,
	};

	err = ovl_want_write(dentry);
	if (err)
		goto out;

	/* Preallocate inode to be used by ovl_get_inode() */
	err = -ENOMEM;
	inode = ovl_new_inode(dentry->d_sb, mode, rdev);
	if (!inode)
		goto out_drop_write;

	spin_lock(&inode->i_lock);
	inode->i_state |= I_CREATING;
	spin_unlock(&inode->i_lock);

	inode_init_owner(inode, dentry->d_parent->d_inode, mode);
	attr.mode = inode->i_mode;

	err = ovl_create_or_link(dentry, inode, &attr, false);
	/* Did we end up using the preallocated inode? */
	if (inode != d_inode(dentry))
		iput(inode);

out_drop_write:
	ovl_drop_write(dentry);
out:
	return err;
}