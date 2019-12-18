#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dentry {int d_flags; TYPE_1__* d_sb; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 scalar_t__ NFS_STALE (int /*<<< orphan*/ ) ; 
 int SB_ACTIVE ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  d_inode (struct dentry const*) ; 
 scalar_t__ d_really_is_positive (struct dentry const*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct dentry const*,int) ; 

__attribute__((used)) static int nfs_dentry_delete(const struct dentry *dentry)
{
	dfprintk(VFS, "NFS: dentry_delete(%pd2, %x)\n",
		dentry, dentry->d_flags);

	/* Unhash any dentry with a stale inode */
	if (d_really_is_positive(dentry) && NFS_STALE(d_inode(dentry)))
		return 1;

	if (dentry->d_flags & DCACHE_NFSFS_RENAMED) {
		/* Unhash it, so that ->d_iput() would be called */
		return 1;
	}
	if (!(dentry->d_sb->s_flags & SB_ACTIVE)) {
		/* Unhash it, so that ancestors of killed async unlink
		 * files will be cleaned up during umount */
		return 1;
	}
	return 0;

}