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
struct nfs_fattr {int valid; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  gencount; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_lock; void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct iattr {int ia_valid; int ia_mode; void* ia_mtime; void* ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_size; } ;
struct TYPE_2__ {int cache_validity; int /*<<< orphan*/  attr_gencount; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  NFSIOS_SETATTRTRUNC ; 
 int NFS_ATTR_FATTR_ATIME ; 
 int NFS_ATTR_FATTR_CTIME ; 
 int NFS_ATTR_FATTR_MTIME ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ACCESS ; 
 int NFS_INO_INVALID_ACL ; 
 int NFS_INO_INVALID_ATIME ; 
 int NFS_INO_INVALID_CHANGE ; 
 int NFS_INO_INVALID_CTIME ; 
 int NFS_INO_INVALID_MTIME ; 
 int S_IALLUGO ; 
 int /*<<< orphan*/  nfs_fattr_set_barrier (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_set_cache_invalid (struct inode*,int) ; 
 int /*<<< orphan*/  nfs_update_inode (struct inode*,struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_vmtruncate (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* timespec_to_timespec64 (int /*<<< orphan*/ ) ; 

void nfs_setattr_update_inode(struct inode *inode, struct iattr *attr,
		struct nfs_fattr *fattr)
{
	/* Barrier: bump the attribute generation count. */
	nfs_fattr_set_barrier(fattr);

	spin_lock(&inode->i_lock);
	NFS_I(inode)->attr_gencount = fattr->gencount;
	if ((attr->ia_valid & ATTR_SIZE) != 0) {
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_MTIME);
		nfs_inc_stats(inode, NFSIOS_SETATTRTRUNC);
		nfs_vmtruncate(inode, attr->ia_size);
	}
	if ((attr->ia_valid & (ATTR_MODE|ATTR_UID|ATTR_GID)) != 0) {
		NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_CTIME;
		if ((attr->ia_valid & ATTR_MODE) != 0) {
			int mode = attr->ia_mode & S_IALLUGO;
			mode |= inode->i_mode & ~S_IALLUGO;
			inode->i_mode = mode;
		}
		if ((attr->ia_valid & ATTR_UID) != 0)
			inode->i_uid = attr->ia_uid;
		if ((attr->ia_valid & ATTR_GID) != 0)
			inode->i_gid = attr->ia_gid;
		if (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_ctime = timespec_to_timespec64(fattr->ctime);
		else
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE
					| NFS_INO_INVALID_CTIME);
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_ACCESS
				| NFS_INO_INVALID_ACL);
	}
	if (attr->ia_valid & (ATTR_ATIME_SET|ATTR_ATIME)) {
		NFS_I(inode)->cache_validity &= ~(NFS_INO_INVALID_ATIME
				| NFS_INO_INVALID_CTIME);
		if (fattr->valid & NFS_ATTR_FATTR_ATIME)
			inode->i_atime = timespec_to_timespec64(fattr->atime);
		else if (attr->ia_valid & ATTR_ATIME_SET)
			inode->i_atime = attr->ia_atime;
		else
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATIME);

		if (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_ctime = timespec_to_timespec64(fattr->ctime);
		else
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE
					| NFS_INO_INVALID_CTIME);
	}
	if (attr->ia_valid & (ATTR_MTIME_SET|ATTR_MTIME)) {
		NFS_I(inode)->cache_validity &= ~(NFS_INO_INVALID_MTIME
				| NFS_INO_INVALID_CTIME);
		if (fattr->valid & NFS_ATTR_FATTR_MTIME)
			inode->i_mtime = timespec_to_timespec64(fattr->mtime);
		else if (attr->ia_valid & ATTR_MTIME_SET)
			inode->i_mtime = attr->ia_mtime;
		else
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_MTIME);

		if (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_ctime = timespec_to_timespec64(fattr->ctime);
		else
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE
					| NFS_INO_INVALID_CTIME);
	}
	if (fattr->valid)
		nfs_update_inode(inode, fattr);
	spin_unlock(&inode->i_lock);
}