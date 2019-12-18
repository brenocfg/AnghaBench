#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct path {struct dentry* dentry; } ;
struct kstat {int attributes_mask; int attributes; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  btime; int /*<<< orphan*/  result_mask; int /*<<< orphan*/  ino; int /*<<< orphan*/  blksize; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cifs_tcon {int /*<<< orphan*/  unix_ext; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  bsize; } ;
struct TYPE_6__ {int cifsAttrs; scalar_t__ createtime; int /*<<< orphan*/  uniqueid; } ;
struct TYPE_5__ {scalar_t__ nrpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (TYPE_3__*) ; 
 TYPE_3__* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_CIFS_ACL ; 
 int CIFS_MOUNT_MULTIUSER ; 
 int CIFS_MOUNT_OVERR_GID ; 
 int CIFS_MOUNT_OVERR_UID ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int FILE_ATTRIBUTE_COMPRESSED ; 
 int FILE_ATTRIBUTE_ENCRYPTED ; 
 int STATX_ATTR_COMPRESSED ; 
 int STATX_ATTR_ENCRYPTED ; 
 int /*<<< orphan*/  STATX_BTIME ; 
 int /*<<< orphan*/  cifs_NTtimeToUnix (int /*<<< orphan*/ ) ; 
 int cifs_revalidate_dentry_attr (struct dentry*) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 struct inode* d_inode (struct dentry*) ; 
 int filemap_fdatawait (TYPE_1__*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  mapping_set_error (TYPE_1__*,int) ; 

int cifs_getattr(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int flags)
{
	struct dentry *dentry = path->dentry;
	struct cifs_sb_info *cifs_sb = CIFS_SB(dentry->d_sb);
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	struct inode *inode = d_inode(dentry);
	int rc;

	/*
	 * We need to be sure that all dirty pages are written and the server
	 * has actual ctime, mtime and file length.
	 */
	if (!CIFS_CACHE_READ(CIFS_I(inode)) && inode->i_mapping &&
	    inode->i_mapping->nrpages != 0) {
		rc = filemap_fdatawait(inode->i_mapping);
		if (rc) {
			mapping_set_error(inode->i_mapping, rc);
			return rc;
		}
	}

	rc = cifs_revalidate_dentry_attr(dentry);
	if (rc)
		return rc;

	generic_fillattr(inode, stat);
	stat->blksize = cifs_sb->bsize;
	stat->ino = CIFS_I(inode)->uniqueid;

	/* old CIFS Unix Extensions doesn't return create time */
	if (CIFS_I(inode)->createtime) {
		stat->result_mask |= STATX_BTIME;
		stat->btime =
		      cifs_NTtimeToUnix(cpu_to_le64(CIFS_I(inode)->createtime));
	}

	stat->attributes_mask |= (STATX_ATTR_COMPRESSED | STATX_ATTR_ENCRYPTED);
	if (CIFS_I(inode)->cifsAttrs & FILE_ATTRIBUTE_COMPRESSED)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	if (CIFS_I(inode)->cifsAttrs & FILE_ATTRIBUTE_ENCRYPTED)
		stat->attributes |= STATX_ATTR_ENCRYPTED;

	/*
	 * If on a multiuser mount without unix extensions or cifsacl being
	 * enabled, and the admin hasn't overridden them, set the ownership
	 * to the fsuid/fsgid of the current process.
	 */
	if ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_MULTIUSER) &&
	    !(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_ACL) &&
	    !tcon->unix_ext) {
		if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_OVERR_UID))
			stat->uid = current_fsuid();
		if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_OVERR_GID))
			stat->gid = current_fsgid();
	}
	return rc;
}