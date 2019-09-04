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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 

int simple_unlink(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);

	inode->i_ctime = dir->i_ctime = dir->i_mtime = current_time(inode);
	drop_nlink(inode);
	dput(dentry);
	return 0;
}