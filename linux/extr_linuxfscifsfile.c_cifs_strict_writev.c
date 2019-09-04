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
struct kiocb {TYPE_2__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  Capability; } ;
struct cifs_tcon {TYPE_1__ fsUnixInfo; int /*<<< orphan*/  ses; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;
struct cifsInodeInfo {scalar_t__ oplock; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {scalar_t__ private_data; } ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 scalar_t__ CIFS_CACHE_WRITE (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int CIFS_MOUNT_NOPOSIXBRL ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CIFS_UNIX_FCNTL_CAP ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ cap_unix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct inode*) ; 
 scalar_t__ cifs_get_writer (struct cifsInodeInfo*) ; 
 int /*<<< orphan*/  cifs_put_writer (struct cifsInodeInfo*) ; 
 scalar_t__ cifs_user_writev (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ cifs_writev (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  cifs_zap_mapping (struct inode*) ; 
 struct inode* file_inode (TYPE_2__*) ; 
 scalar_t__ generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 

ssize_t
cifs_strict_writev(struct kiocb *iocb, struct iov_iter *from)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	struct cifsInodeInfo *cinode = CIFS_I(inode);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct cifsFileInfo *cfile = (struct cifsFileInfo *)
						iocb->ki_filp->private_data;
	struct cifs_tcon *tcon = tlink_tcon(cfile->tlink);
	ssize_t written;

	written = cifs_get_writer(cinode);
	if (written)
		return written;

	if (CIFS_CACHE_WRITE(cinode)) {
		if (cap_unix(tcon->ses) &&
		(CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability))
		  && ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0)) {
			written = generic_file_write_iter(iocb, from);
			goto out;
		}
		written = cifs_writev(iocb, from);
		goto out;
	}
	/*
	 * For non-oplocked files in strict cache mode we need to write the data
	 * to the server exactly from the pos to pos+len-1 rather than flush all
	 * affected pages because it may cause a error with mandatory locks on
	 * these pages but not on the region from pos to ppos+len-1.
	 */
	written = cifs_user_writev(iocb, from);
	if (CIFS_CACHE_READ(cinode)) {
		/*
		 * We have read level caching and we have just sent a write
		 * request to the server thus making data in the cache stale.
		 * Zap the cache and set oplock/lease level to NONE to avoid
		 * reading stale data from the cache. All subsequent read
		 * operations will read new data from the server.
		 */
		cifs_zap_mapping(inode);
		cifs_dbg(FYI, "Set Oplock/Lease to NONE for inode=%p after write\n",
			 inode);
		cinode->oplock = 0;
	}
out:
	cifs_put_writer(cinode);
	return written;
}