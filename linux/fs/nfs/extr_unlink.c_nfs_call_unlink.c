#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct nfs_unlinkdata {struct dentry* dentry; int /*<<< orphan*/  wq; TYPE_1__ args; } ;
struct inode {int dummy; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; struct nfs_unlinkdata* d_fsdata; int /*<<< orphan*/  d_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  rmdir_sem; } ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 struct dentry* d_alloc_parallel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  down_read_non_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  nfs_do_call_unlink (struct inode*,struct nfs_unlinkdata*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read_non_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_call_unlink(struct dentry *dentry, struct inode *inode, struct nfs_unlinkdata *data)
{
	struct inode *dir = d_inode(dentry->d_parent);
	struct dentry *alias;

	down_read_non_owner(&NFS_I(dir)->rmdir_sem);
	alias = d_alloc_parallel(dentry->d_parent, &data->args.name, &data->wq);
	if (IS_ERR(alias)) {
		up_read_non_owner(&NFS_I(dir)->rmdir_sem);
		return 0;
	}
	if (!d_in_lookup(alias)) {
		int ret;
		void *devname_garbage = NULL;

		/*
		 * Hey, we raced with lookup... See if we need to transfer
		 * the sillyrename information to the aliased dentry.
		 */
		spin_lock(&alias->d_lock);
		if (d_really_is_positive(alias) &&
		    !(alias->d_flags & DCACHE_NFSFS_RENAMED)) {
			devname_garbage = alias->d_fsdata;
			alias->d_fsdata = data;
			alias->d_flags |= DCACHE_NFSFS_RENAMED;
			ret = 1;
		} else
			ret = 0;
		spin_unlock(&alias->d_lock);
		dput(alias);
		up_read_non_owner(&NFS_I(dir)->rmdir_sem);
		/*
		 * If we'd displaced old cached devname, free it.  At that
		 * point dentry is definitely not a root, so we won't need
		 * that anymore.
		 */
		kfree(devname_garbage);
		return ret;
	}
	data->dentry = alias;
	nfs_do_call_unlink(inode, data);
	return 1;
}