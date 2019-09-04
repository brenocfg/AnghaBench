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
struct kiocb {scalar_t__ ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 scalar_t__ blockdev_direct_IO (struct kiocb*,struct inode*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 int /*<<< orphan*/  jfs_get_block ; 
 int /*<<< orphan*/  jfs_write_failed (struct address_space*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t jfs_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	struct inode *inode = file->f_mapping->host;
	size_t count = iov_iter_count(iter);
	ssize_t ret;

	ret = blockdev_direct_IO(iocb, inode, iter, jfs_get_block);

	/*
	 * In case of error extending write may have instantiated a few
	 * blocks outside i_size. Trim these off again.
	 */
	if (unlikely(iov_iter_rw(iter) == WRITE && ret < 0)) {
		loff_t isize = i_size_read(inode);
		loff_t end = iocb->ki_pos + count;

		if (end > isize)
			jfs_write_failed(mapping, end);
	}

	return ret;
}