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
struct inode {int dummy; } ;
struct file {struct cifsFileInfo* private_data; } ;
struct cifs_tcon {TYPE_2__* ses; int /*<<< orphan*/  tid; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
struct TYPE_3__ {int /*<<< orphan*/  persistent_fid; int /*<<< orphan*/  volatile_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; int /*<<< orphan*/  pid; int /*<<< orphan*/  dentry; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_4__ {int /*<<< orphan*/  Suid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 long EOPNOTSUPP ; 
 int FILE_ATTRIBUTE_SPARSE_FILE ; 
 long SMB2_set_eof (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  smb2_set_sparse (unsigned int,struct cifs_tcon*,struct cifsFileInfo*,struct inode*,int) ; 
 int /*<<< orphan*/  trace_smb3_falloc_done (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_smb3_falloc_enter (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_smb3_falloc_err (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,long) ; 

__attribute__((used)) static long smb3_simple_falloc(struct file *file, struct cifs_tcon *tcon,
			    loff_t off, loff_t len, bool keep_size)
{
	struct inode *inode;
	struct cifsInodeInfo *cifsi;
	struct cifsFileInfo *cfile = file->private_data;
	long rc = -EOPNOTSUPP;
	unsigned int xid;
	__le64 eof;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cifsi = CIFS_I(inode);

	trace_smb3_falloc_enter(xid, cfile->fid.persistent_fid, tcon->tid,
				tcon->ses->Suid, off, len);
	/* if file not oplocked can't be sure whether asking to extend size */
	if (!CIFS_CACHE_READ(cifsi))
		if (keep_size == false) {
			trace_smb3_falloc_err(xid, cfile->fid.persistent_fid,
				tcon->tid, tcon->ses->Suid, off, len, rc);
			free_xid(xid);
			return rc;
		}

	/*
	 * Files are non-sparse by default so falloc may be a no-op
	 * Must check if file sparse. If not sparse, and not extending
	 * then no need to do anything since file already allocated
	 */
	if ((cifsi->cifsAttrs & FILE_ATTRIBUTE_SPARSE_FILE) == 0) {
		if (keep_size == true)
			rc = 0;
		/* check if extending file */
		else if (i_size_read(inode) >= off + len)
			/* not extending file and already not sparse */
			rc = 0;
		/* BB: in future add else clause to extend file */
		else
			rc = -EOPNOTSUPP;
		if (rc)
			trace_smb3_falloc_err(xid, cfile->fid.persistent_fid,
				tcon->tid, tcon->ses->Suid, off, len, rc);
		else
			trace_smb3_falloc_done(xid, cfile->fid.persistent_fid,
				tcon->tid, tcon->ses->Suid, off, len);
		free_xid(xid);
		return rc;
	}

	if ((keep_size == true) || (i_size_read(inode) >= off + len)) {
		/*
		 * Check if falloc starts within first few pages of file
		 * and ends within a few pages of the end of file to
		 * ensure that most of file is being forced to be
		 * fallocated now. If so then setting whole file sparse
		 * ie potentially making a few extra pages at the beginning
		 * or end of the file non-sparse via set_sparse is harmless.
		 */
		if ((off > 8192) || (off + len + 8192 < i_size_read(inode))) {
			rc = -EOPNOTSUPP;
			trace_smb3_falloc_err(xid, cfile->fid.persistent_fid,
				tcon->tid, tcon->ses->Suid, off, len, rc);
			free_xid(xid);
			return rc;
		}

		smb2_set_sparse(xid, tcon, cfile, inode, false);
		rc = 0;
	} else {
		smb2_set_sparse(xid, tcon, cfile, inode, false);
		rc = 0;
		if (i_size_read(inode) < off + len) {
			eof = cpu_to_le64(off + len);
			rc = SMB2_set_eof(xid, tcon, cfile->fid.persistent_fid,
					  cfile->fid.volatile_fid, cfile->pid,
					  &eof);
		}
	}

	if (rc)
		trace_smb3_falloc_err(xid, cfile->fid.persistent_fid, tcon->tid,
				tcon->ses->Suid, off, len, rc);
	else
		trace_smb3_falloc_done(xid, cfile->fid.persistent_fid, tcon->tid,
				tcon->ses->Suid, off, len);

	free_xid(xid);
	return rc;
}