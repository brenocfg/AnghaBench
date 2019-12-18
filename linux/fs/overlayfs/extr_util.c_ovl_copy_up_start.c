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
struct dentry {int dummy; } ;

/* Variables and functions */
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ ovl_already_copied_up_locked (struct dentry*,int) ; 
 int ovl_inode_lock (struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_unlock (struct inode*) ; 

int ovl_copy_up_start(struct dentry *dentry, int flags)
{
	struct inode *inode = d_inode(dentry);
	int err;

	err = ovl_inode_lock(inode);
	if (!err && ovl_already_copied_up_locked(dentry, flags)) {
		err = 1; /* Already copied up */
		ovl_inode_unlock(inode);
	}

	return err;
}