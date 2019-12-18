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
struct kiocb {scalar_t__ ki_pos; TYPE_2__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {struct address_space* f_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 scalar_t__ __blockdev_direct_IO (struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_dio_get_block ; 
 scalar_t__ filemap_write_and_wait_range (struct address_space*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 

__attribute__((used)) static ssize_t ext4_direct_IO_read(struct kiocb *iocb, struct iov_iter *iter)
{
	struct address_space *mapping = iocb->ki_filp->f_mapping;
	struct inode *inode = mapping->host;
	size_t count = iov_iter_count(iter);
	ssize_t ret;

	/*
	 * Shared inode_lock is enough for us - it protects against concurrent
	 * writes & truncates and since we take care of writing back page cache,
	 * we are protected against page writeback as well.
	 */
	inode_lock_shared(inode);
	ret = filemap_write_and_wait_range(mapping, iocb->ki_pos,
					   iocb->ki_pos + count - 1);
	if (ret)
		goto out_unlock;
	ret = __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev,
				   iter, ext4_dio_get_block, NULL, NULL, 0);
out_unlock:
	inode_unlock_shared(inode);
	return ret;
}