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
struct inode {scalar_t__ i_size; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 scalar_t__ sysv_empty_dir (struct inode*) ; 
 int sysv_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static int sysv_rmdir(struct inode * dir, struct dentry * dentry)
{
	struct inode *inode = d_inode(dentry);
	int err = -ENOTEMPTY;

	if (sysv_empty_dir(inode)) {
		err = sysv_unlink(dir, dentry);
		if (!err) {
			inode->i_size = 0;
			inode_dec_link_count(inode);
			inode_dec_link_count(dir);
		}
	}
	return err;
}