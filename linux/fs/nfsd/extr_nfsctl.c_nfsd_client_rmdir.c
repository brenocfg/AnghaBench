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
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_ncl (struct inode*) ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  nfsdfs_remove_files (struct dentry*) ; 
 int simple_rmdir (struct inode*,struct dentry*) ; 

void nfsd_client_rmdir(struct dentry *dentry)
{
	struct inode *dir = d_inode(dentry->d_parent);
	struct inode *inode = d_inode(dentry);
	int ret;

	inode_lock(dir);
	nfsdfs_remove_files(dentry);
	clear_ncl(inode);
	dget(dentry);
	ret = simple_rmdir(dir, dentry);
	WARN_ON_ONCE(ret);
	d_delete(dentry);
	inode_unlock(dir);
}