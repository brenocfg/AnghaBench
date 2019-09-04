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
struct inode {int dummy; } ;
struct file {struct cifsFileInfo* private_data; } ;
struct cifs_tcon {int dummy; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
struct cifsFileInfo {int /*<<< orphan*/  dentry; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 long EOPNOTSUPP ; 
 int FILE_ATTRIBUTE_SPARSE_FILE ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 scalar_t__ i_size_read (struct inode*) ; 
 long smb2_set_sparse (unsigned int,struct cifs_tcon*,struct cifsFileInfo*,struct inode*,int) ; 

__attribute__((used)) static long smb3_simple_falloc(struct file *file, struct cifs_tcon *tcon,
			    loff_t off, loff_t len, bool keep_size)
{
	struct inode *inode;
	struct cifsInodeInfo *cifsi;
	struct cifsFileInfo *cfile = file->private_data;
	long rc = -EOPNOTSUPP;
	unsigned int xid;

	xid = get_xid();

	inode = d_inode(cfile->dentry);
	cifsi = CIFS_I(inode);

	/* if file not oplocked can't be sure whether asking to extend size */
	if (!CIFS_CACHE_READ(cifsi))
		if (keep_size == false) {
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
			free_xid(xid);
			return rc;
		}

		rc = smb2_set_sparse(xid, tcon, cfile, inode, false);
	}
	/* BB: else ... in future add code to extend file and set sparse */


	free_xid(xid);
	return rc;
}