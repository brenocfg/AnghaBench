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
struct nfs_unlinkdata {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_lock; struct nfs_unlinkdata* d_fsdata; int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_NFSFS_RENAMED ; 
 scalar_t__ NFS_STALE (struct inode*) ; 
 int /*<<< orphan*/  nfs_call_unlink (struct dentry*,struct inode*,struct nfs_unlinkdata*) ; 
 int /*<<< orphan*/  nfs_free_unlinkdata (struct nfs_unlinkdata*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
nfs_complete_unlink(struct dentry *dentry, struct inode *inode)
{
	struct nfs_unlinkdata	*data;

	spin_lock(&dentry->d_lock);
	dentry->d_flags &= ~DCACHE_NFSFS_RENAMED;
	data = dentry->d_fsdata;
	dentry->d_fsdata = NULL;
	spin_unlock(&dentry->d_lock);

	if (NFS_STALE(inode) || !nfs_call_unlink(dentry, inode, data))
		nfs_free_unlinkdata(data);
}