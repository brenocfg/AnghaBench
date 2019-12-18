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
struct cifs_tcon {int broken_sparse_sup; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSMaxBufSize ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int FILE_ATTRIBUTE_SPARSE_FILE ; 
 int /*<<< orphan*/  FSCTL_SET_SPARSE ; 
 int /*<<< orphan*/  FYI ; 
 int SMB2_ioctl (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool smb2_set_sparse(const unsigned int xid, struct cifs_tcon *tcon,
		struct cifsFileInfo *cfile, struct inode *inode, __u8 setsparse)
{
	struct cifsInodeInfo *cifsi;
	int rc;

	cifsi = CIFS_I(inode);

	/* if file already sparse don't bother setting sparse again */
	if ((cifsi->cifsAttrs & FILE_ATTRIBUTE_SPARSE_FILE) && setsparse)
		return true; /* already sparse */

	if (!(cifsi->cifsAttrs & FILE_ATTRIBUTE_SPARSE_FILE) && !setsparse)
		return true; /* already not sparse */

	/*
	 * Can't check for sparse support on share the usual way via the
	 * FS attribute info (FILE_SUPPORTS_SPARSE_FILES) on the share
	 * since Samba server doesn't set the flag on the share, yet
	 * supports the set sparse FSCTL and returns sparse correctly
	 * in the file attributes. If we fail setting sparse though we
	 * mark that server does not support sparse files for this share
	 * to avoid repeatedly sending the unsupported fsctl to server
	 * if the file is repeatedly extended.
	 */
	if (tcon->broken_sparse_sup)
		return false;

	rc = SMB2_ioctl(xid, tcon, cfile->fid.persistent_fid,
			cfile->fid.volatile_fid, FSCTL_SET_SPARSE,
			true /* is_fctl */,
			&setsparse, 1, CIFSMaxBufSize, NULL, NULL);
	if (rc) {
		tcon->broken_sparse_sup = true;
		cifs_dbg(FYI, "set sparse rc = %d\n", rc);
		return false;
	}

	if (setsparse)
		cifsi->cifsAttrs |= FILE_ATTRIBUTE_SPARSE_FILE;
	else
		cifsi->cifsAttrs &= (~FILE_ATTRIBUTE_SPARSE_FILE);

	return true;
}