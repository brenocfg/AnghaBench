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
struct kiocb {int ki_flags; int /*<<< orphan*/  ki_pos; int /*<<< orphan*/  ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_io_priv {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_DIO_WRITE ; 
 struct fuse_io_priv FUSE_IO_PRIV_SYNC (struct kiocb*) ; 
 int IOCB_DIRECT ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_direct_IO (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ fuse_direct_io (struct fuse_io_priv*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 

__attribute__((used)) static ssize_t fuse_direct_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	struct fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);
	ssize_t res;

	/* Don't allow parallel writes to the same file */
	inode_lock(inode);
	res = generic_write_checks(iocb, from);
	if (res > 0) {
		if (!is_sync_kiocb(iocb) && iocb->ki_flags & IOCB_DIRECT) {
			res = fuse_direct_IO(iocb, from);
		} else {
			res = fuse_direct_io(&io, from, &iocb->ki_pos,
					     FUSE_DIO_WRITE);
		}
	}
	fuse_invalidate_attr(inode);
	if (res > 0)
		fuse_write_update_size(inode, iocb->ki_pos);
	inode_unlock(inode);

	return res;
}