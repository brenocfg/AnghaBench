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
struct kiocb {int ki_pos; int /*<<< orphan*/  ki_filp; } ;
struct iomap_dio_ops {scalar_t__ (* end_io ) (struct kiocb*,scalar_t__,scalar_t__,int) ;} ;
struct iomap_dio {scalar_t__ error; scalar_t__ size; int flags; scalar_t__ i_size; struct kiocb* iocb; struct iomap_dio_ops* dops; } ;
struct inode {TYPE_1__* i_mapping; } ;
typedef  scalar_t__ ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {scalar_t__ nrpages; } ;

/* Variables and functions */
 int IOMAP_DIO_NEED_SYNC ; 
 int IOMAP_DIO_WRITE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dio_warn_stale_pagecache (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ generic_write_sync (struct kiocb*,scalar_t__) ; 
 int /*<<< orphan*/  inode_dio_end (struct inode*) ; 
 int invalidate_inode_pages2_range (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  kfree (struct iomap_dio*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ stub1 (struct kiocb*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static ssize_t iomap_dio_complete(struct iomap_dio *dio)
{
	const struct iomap_dio_ops *dops = dio->dops;
	struct kiocb *iocb = dio->iocb;
	struct inode *inode = file_inode(iocb->ki_filp);
	loff_t offset = iocb->ki_pos;
	ssize_t ret = dio->error;

	if (dops && dops->end_io)
		ret = dops->end_io(iocb, dio->size, ret, dio->flags);

	if (likely(!ret)) {
		ret = dio->size;
		/* check for short read */
		if (offset + ret > dio->i_size &&
		    !(dio->flags & IOMAP_DIO_WRITE))
			ret = dio->i_size - offset;
		iocb->ki_pos += ret;
	}

	/*
	 * Try again to invalidate clean pages which might have been cached by
	 * non-direct readahead, or faulted in by get_user_pages() if the source
	 * of the write was an mmap'ed region of the file we're writing.  Either
	 * one is a pretty crazy thing to do, so we don't support it 100%.  If
	 * this invalidation fails, tough, the write still worked...
	 *
	 * And this page cache invalidation has to be after ->end_io(), as some
	 * filesystems convert unwritten extents to real allocations in
	 * ->end_io() when necessary, otherwise a racing buffer read would cache
	 * zeros from unwritten extents.
	 */
	if (!dio->error &&
	    (dio->flags & IOMAP_DIO_WRITE) && inode->i_mapping->nrpages) {
		int err;
		err = invalidate_inode_pages2_range(inode->i_mapping,
				offset >> PAGE_SHIFT,
				(offset + dio->size - 1) >> PAGE_SHIFT);
		if (err)
			dio_warn_stale_pagecache(iocb->ki_filp);
	}

	/*
	 * If this is a DSYNC write, make sure we push it to stable storage now
	 * that we've written data.
	 */
	if (ret > 0 && (dio->flags & IOMAP_DIO_NEED_SYNC))
		ret = generic_write_sync(iocb, ret);

	inode_dio_end(file_inode(iocb->ki_filp));
	kfree(dio);

	return ret;
}