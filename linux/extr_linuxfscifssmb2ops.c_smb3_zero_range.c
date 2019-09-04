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
struct inode {int dummy; } ;
struct file_zero_data_information {void* BeyondFinalZero; void* FileOffset; } ;
struct file {struct cifsFileInfo* private_data; } ;
struct cifs_tcon {int dummy; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; int /*<<< orphan*/  dentry; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 long EOPNOTSUPP ; 
 int FILE_ATTRIBUTE_SPARSE_FILE ; 
 int /*<<< orphan*/  FSCTL_SET_ZERO_DATA ; 
 int /*<<< orphan*/  FYI ; 
 long SMB2_ioctl (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 scalar_t__ i_size_read (struct inode*) ; 

__attribute__((used)) static long smb3_zero_range(struct file *file, struct cifs_tcon *tcon,
			    loff_t offset, loff_t len, bool keep_size)
{
	struct inode *inode;
	struct cifsInodeInfo *cifsi;
	struct cifsFileInfo *cfile = file->private_data;
	struct file_zero_data_information fsctl_buf;
	long rc;
	unsigned int xid;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cifsi = CIFS_I(inode);

	/* if file not oplocked can't be sure whether asking to extend size */
	if (!CIFS_CACHE_READ(cifsi))
		if (keep_size == false) {
			rc = -EOPNOTSUPP;
			free_xid(xid);
			return rc;
		}

	/*
	 * Must check if file sparse since fallocate -z (zero range) assumes
	 * non-sparse allocation
	 */
	if (!(cifsi->cifsAttrs & FILE_ATTRIBUTE_SPARSE_FILE)) {
		rc = -EOPNOTSUPP;
		free_xid(xid);
		return rc;
	}

	/*
	 * need to make sure we are not asked to extend the file since the SMB3
	 * fsctl does not change the file size. In the future we could change
	 * this to zero the first part of the range then set the file size
	 * which for a non sparse file would zero the newly extended range
	 */
	if (keep_size == false)
		if (i_size_read(inode) < offset + len) {
			rc = -EOPNOTSUPP;
			free_xid(xid);
			return rc;
		}

	cifs_dbg(FYI, "offset %lld len %lld", offset, len);

	fsctl_buf.FileOffset = cpu_to_le64(offset);
	fsctl_buf.BeyondFinalZero = cpu_to_le64(offset + len);

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.volatile_fid, FSCTL_SET_ZERO_DATA,
			true /* is_fctl */, (char *)&fsctl_buf,
			sizeof(struct file_zero_data_information), NULL, NULL);
	free_xid(xid);
	return rc;
}