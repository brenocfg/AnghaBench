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
 int ENOTEMPTY ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ f2fs_empty_dir (struct inode*) ; 
 int f2fs_unlink (struct inode*,struct dentry*) ; 

__attribute__((used)) static int f2fs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	if (f2fs_empty_dir(inode))
		return f2fs_unlink(dir, dentry);
	return -ENOTEMPTY;
}