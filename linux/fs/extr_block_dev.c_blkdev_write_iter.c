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
struct kiocb {scalar_t__ ki_pos; int ki_flags; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct blk_plug {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 scalar_t__ EOPNOTSUPP ; 
 scalar_t__ EPERM ; 
 scalar_t__ ETXTBSY ; 
 int IOCB_DIRECT ; 
 int IOCB_NOWAIT ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int /*<<< orphan*/  I_BDEV (struct inode*) ; 
 scalar_t__ __generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 
 struct inode* bdev_file_inode (struct file*) ; 
 scalar_t__ bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 scalar_t__ generic_write_sync (struct kiocb*,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,scalar_t__) ; 

ssize_t blkdev_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct inode *bd_inode = bdev_file_inode(file);
	loff_t size = i_size_read(bd_inode);
	struct blk_plug plug;
	ssize_t ret;

	if (bdev_read_only(I_BDEV(bd_inode)))
		return -EPERM;

	if (IS_SWAPFILE(bd_inode))
		return -ETXTBSY;

	if (!iov_iter_count(from))
		return 0;

	if (iocb->ki_pos >= size)
		return -ENOSPC;

	if ((iocb->ki_flags & (IOCB_NOWAIT | IOCB_DIRECT)) == IOCB_NOWAIT)
		return -EOPNOTSUPP;

	iov_iter_truncate(from, size - iocb->ki_pos);

	blk_start_plug(&plug);
	ret = __generic_file_write_iter(iocb, from);
	if (ret > 0)
		ret = generic_write_sync(iocb, ret);
	blk_finish_plug(&plug);
	return ret;
}