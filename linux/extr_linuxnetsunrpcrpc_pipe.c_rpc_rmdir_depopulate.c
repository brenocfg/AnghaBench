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
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int __rpc_rmdir (struct inode*,struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static int rpc_rmdir_depopulate(struct dentry *dentry,
		void (*depopulate)(struct dentry *))
{
	struct dentry *parent;
	struct inode *dir;
	int error;

	parent = dget_parent(dentry);
	dir = d_inode(parent);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	if (depopulate != NULL)
		depopulate(dentry);
	error = __rpc_rmdir(dir, dentry);
	inode_unlock(dir);
	dput(parent);
	return error;
}