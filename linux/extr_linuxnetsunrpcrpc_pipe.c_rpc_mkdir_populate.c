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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 struct dentry* __rpc_lookup_create_exclusive (struct dentry*,char const*) ; 
 int __rpc_mkdir (struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  __rpc_rmdir (struct inode*,struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static struct dentry *rpc_mkdir_populate(struct dentry *parent,
		const char *name, umode_t mode, void *private,
		int (*populate)(struct dentry *, void *), void *args_populate)
{
	struct dentry *dentry;
	struct inode *dir = d_inode(parent);
	int error;

	inode_lock_nested(dir, I_MUTEX_PARENT);
	dentry = __rpc_lookup_create_exclusive(parent, name);
	if (IS_ERR(dentry))
		goto out;
	error = __rpc_mkdir(dir, dentry, mode, NULL, private);
	if (error != 0)
		goto out_err;
	if (populate != NULL) {
		error = populate(dentry, args_populate);
		if (error)
			goto err_rmdir;
	}
out:
	inode_unlock(dir);
	return dentry;
err_rmdir:
	__rpc_rmdir(dir, dentry);
out_err:
	dentry = ERR_PTR(error);
	goto out;
}