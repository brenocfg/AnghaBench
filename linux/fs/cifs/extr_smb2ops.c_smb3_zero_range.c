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
struct cifs_tcon {int /*<<< orphan*/  tid; struct cifs_ses* ses; } ;
struct cifs_ses {int /*<<< orphan*/  Suid; } ;
struct cifsInodeInfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  persistent_fid; int /*<<< orphan*/  volatile_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; int /*<<< orphan*/  pid; int /*<<< orphan*/  dentry; } ;
typedef  scalar_t__ loff_t ;
typedef  void* __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 long EOPNOTSUPP ; 
 int /*<<< orphan*/  FSCTL_SET_ZERO_DATA ; 
 int /*<<< orphan*/  FYI ; 
 long SMB2_ioctl (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long SMB2_set_eof (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  trace_smb3_zero_done (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_smb3_zero_enter (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_smb3_zero_err (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,long) ; 

__attribute__((used)) static long smb3_zero_range(struct file *file, struct cifs_tcon *tcon,
			    loff_t offset, loff_t len, bool keep_size)
{
	struct cifs_ses *ses = tcon->ses;
	struct inode *inode;
	struct cifsInodeInfo *cifsi;
	struct cifsFileInfo *cfile = file->private_data;
	struct file_zero_data_information fsctl_buf;
	long rc;
	unsigned int xid;
	__le64 eof;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cifsi = CIFS_I(inode);

	trace_smb3_zero_enter(xid, cfile->fid.persistent_fid, tcon->tid,
			      ses->Suid, offset, len);


	/* if file not oplocked can't be sure whether asking to extend size */
	if (!CIFS_CACHE_READ(cifsi))
		if (keep_size == false) {
			rc = -EOPNOTSUPP;
			trace_smb3_zero_err(xid, cfile->fid.persistent_fid,
				tcon->tid, ses->Suid, offset, len, rc);
			free_xid(xid);
			return rc;
		}

	cifs_dbg(FYI, "Offset %lld len %lld\n", offset, len);

	fsctl_buf.FileOffset = cpu_to_le64(offset);
	fsctl_buf.BeyondFinalZero = cpu_to_le64(offset + len);

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.volatile_fid, FSCTL_SET_ZERO_DATA, true,
			(char *)&fsctl_buf,
			sizeof(struct file_zero_data_information),
			0, NULL, NULL);
	if (rc)
		goto zero_range_exit;

	/*
	 * do we also need to change the size of the file?
	 */
	if (keep_size == false && i_size_read(inode) < offset + len) {
		eof = cpu_to_le64(offset + len);
		rc = SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
				  cfile->fid.volatile_fid, cfile->pid, &eof);
	}

 zero_range_exit:
	free_xid(xid);
	if (rc)
		trace_smb3_zero_err(xid, cfile->fid.persistent_fid, tcon->tid,
			      ses->Suid, offset, len, rc);
	else
		trace_smb3_zero_done(xid, cfile->fid.persistent_fid, tcon->tid,
			      ses->Suid, offset, len);
	return rc;
}