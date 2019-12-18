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
struct timespec {int dummy; } ;
struct nfs_fattr {int valid; int /*<<< orphan*/  size; int /*<<< orphan*/  pre_size; int /*<<< orphan*/  mtime; int /*<<< orphan*/  pre_mtime; int /*<<< orphan*/  ctime; int /*<<< orphan*/  pre_ctime; int /*<<< orphan*/  change_attr; int /*<<< orphan*/  pre_change_attr; } ;
struct inode {int /*<<< orphan*/  i_mode; void* i_mtime; void* i_ctime; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_CHANGE ; 
 int NFS_ATTR_FATTR_CTIME ; 
 int NFS_ATTR_FATTR_MTIME ; 
 int NFS_ATTR_FATTR_PRECHANGE ; 
 int NFS_ATTR_FATTR_PRECTIME ; 
 int NFS_ATTR_FATTR_PREMTIME ; 
 int NFS_ATTR_FATTR_PRESIZE ; 
 int NFS_ATTR_FATTR_SIZE ; 
 int /*<<< orphan*/  NFS_INO_INVALID_DATA ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 scalar_t__ inode_eq_iversion_raw (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_set_iversion_raw (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_have_writebacks (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_cache_invalid (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_size_to_loff_t (int /*<<< orphan*/ ) ; 
 struct timespec timespec64_to_timespec (void*) ; 
 scalar_t__ timespec_equal (struct timespec*,int /*<<< orphan*/ *) ; 
 void* timespec_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_wcc_update_inode(struct inode *inode, struct nfs_fattr *fattr)
{
	struct timespec ts;

	if ((fattr->valid & NFS_ATTR_FATTR_PRECHANGE)
			&& (fattr->valid & NFS_ATTR_FATTR_CHANGE)
			&& inode_eq_iversion_raw(inode, fattr->pre_change_attr)) {
		inode_set_iversion_raw(inode, fattr->change_attr);
		if (S_ISDIR(inode->i_mode))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA);
	}
	/* If we have atomic WCC data, we may update some attributes */
	ts = timespec64_to_timespec(inode->i_ctime);
	if ((fattr->valid & NFS_ATTR_FATTR_PRECTIME)
			&& (fattr->valid & NFS_ATTR_FATTR_CTIME)
			&& timespec_equal(&ts, &fattr->pre_ctime)) {
		inode->i_ctime = timespec_to_timespec64(fattr->ctime);
	}

	ts = timespec64_to_timespec(inode->i_mtime);
	if ((fattr->valid & NFS_ATTR_FATTR_PREMTIME)
			&& (fattr->valid & NFS_ATTR_FATTR_MTIME)
			&& timespec_equal(&ts, &fattr->pre_mtime)) {
		inode->i_mtime = timespec_to_timespec64(fattr->mtime);
		if (S_ISDIR(inode->i_mode))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA);
	}
	if ((fattr->valid & NFS_ATTR_FATTR_PRESIZE)
			&& (fattr->valid & NFS_ATTR_FATTR_SIZE)
			&& i_size_read(inode) == nfs_size_to_loff_t(fattr->pre_size)
			&& !nfs_have_writebacks(inode)) {
		i_size_write(inode, nfs_size_to_loff_t(fattr->size));
	}
}