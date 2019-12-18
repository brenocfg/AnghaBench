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
struct kiocb {TYPE_1__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct cifsInodeInfo {scalar_t__ oplock; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int f_flags; } ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 scalar_t__ CIFS_CACHE_WRITE (struct cifsInodeInfo*) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  FYI ; 
 int O_DIRECT ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ cifs_get_writer (struct cifsInodeInfo*) ; 
 int /*<<< orphan*/  cifs_put_writer (struct cifsInodeInfo*) ; 
 scalar_t__ cifs_user_writev (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  cifs_zap_mapping (struct inode*) ; 
 struct inode* file_inode (TYPE_1__*) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 scalar_t__ generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 

__attribute__((used)) static ssize_t cifs_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	struct cifsInodeInfo *cinode = CIFS_I(inode);
	ssize_t written;
	int rc;

	if (iocb->ki_filp->f_flags & O_DIRECT) {
		written = cifs_user_writev(iocb, from);
		if (written > 0 && CIFS_CACHE_READ(cinode)) {
			cifs_zap_mapping(inode);
			cifs_dbg(FYI,
				 "Set no oplock for inode=%p after a write operation\n",
				 inode);
			cinode->oplock = 0;
		}
		return written;
	}

	written = cifs_get_writer(cinode);
	if (written)
		return written;

	written = generic_file_write_iter(iocb, from);

	if (CIFS_CACHE_WRITE(CIFS_I(inode)))
		goto out;

	rc = filemap_fdatawrite(inode->i_mapping);
	if (rc)
		cifs_dbg(FYI, "cifs_file_write_iter: %d rc on %p inode\n",
			 rc, inode);

out:
	cifs_put_writer(cinode);
	return written;
}