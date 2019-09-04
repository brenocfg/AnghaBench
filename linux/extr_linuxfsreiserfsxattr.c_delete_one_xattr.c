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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int xattr_rmdir (struct inode*,struct dentry*) ; 
 int xattr_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static int delete_one_xattr(struct dentry *dentry, void *data)
{
	struct inode *dir = d_inode(dentry->d_parent);

	/* This is the xattr dir, handle specially. */
	if (d_is_dir(dentry))
		return xattr_rmdir(dir, dentry);

	return xattr_unlink(dir, dentry);
}