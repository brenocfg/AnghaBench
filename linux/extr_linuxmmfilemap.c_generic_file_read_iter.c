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
struct kiocb {int ki_flags; scalar_t__ ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {TYPE_1__* a_ops; struct inode* host; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {size_t (* direct_IO ) (struct kiocb*,struct iov_iter*) ;} ;

/* Variables and functions */
 size_t EAGAIN ; 
 int IOCB_DIRECT ; 
 int IOCB_NOWAIT ; 
 scalar_t__ IS_DAX (struct inode*) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 scalar_t__ filemap_range_has_page (struct address_space*,scalar_t__,scalar_t__) ; 
 size_t filemap_write_and_wait_range (struct address_space*,scalar_t__,scalar_t__) ; 
 size_t generic_file_buffered_read (struct kiocb*,struct iov_iter*,size_t) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_revert (struct iov_iter*,size_t) ; 
 size_t stub1 (struct kiocb*,struct iov_iter*) ; 

ssize_t
generic_file_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	size_t count = iov_iter_count(iter);
	ssize_t retval = 0;

	if (!count)
		goto out; /* skip atime */

	if (iocb->ki_flags & IOCB_DIRECT) {
		struct file *file = iocb->ki_filp;
		struct address_space *mapping = file->f_mapping;
		struct inode *inode = mapping->host;
		loff_t size;

		size = i_size_read(inode);
		if (iocb->ki_flags & IOCB_NOWAIT) {
			if (filemap_range_has_page(mapping, iocb->ki_pos,
						   iocb->ki_pos + count - 1))
				return -EAGAIN;
		} else {
			retval = filemap_write_and_wait_range(mapping,
						iocb->ki_pos,
					        iocb->ki_pos + count - 1);
			if (retval < 0)
				goto out;
		}

		file_accessed(file);

		retval = mapping->a_ops->direct_IO(iocb, iter);
		if (retval >= 0) {
			iocb->ki_pos += retval;
			count -= retval;
		}
		iov_iter_revert(iter, count - iov_iter_count(iter));

		/*
		 * Btrfs can have a short DIO read if we encounter
		 * compressed extents, so if there was an error, or if
		 * we've already read everything we wanted to, or if
		 * there was a short read because we hit EOF, go ahead
		 * and return.  Otherwise fallthrough to buffered io for
		 * the rest of the read.  Buffered reads will not work for
		 * DAX files, so don't bother trying.
		 */
		if (retval < 0 || !count || iocb->ki_pos >= size ||
		    IS_DAX(inode))
			goto out;
	}

	retval = generic_file_buffered_read(iocb, iter, retval);
out:
	return retval;
}