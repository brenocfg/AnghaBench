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
struct kiocb {scalar_t__ ki_pos; int /*<<< orphan*/ * private; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {scalar_t__ i_size; scalar_t__ i_nlink; TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct ext4_inode_info {scalar_t__ i_disksize; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  get_block_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int DIO_LOCKING ; 
 int DIO_SKIP_HOLES ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_DIO_UNWRITTEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ __blockdev_direct_IO (struct kiocb*,struct inode*,int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_convert_unwritten_extents (int /*<<< orphan*/ *,struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ext4_dio_get_block ; 
 int /*<<< orphan*/ * ext4_dio_get_block_overwrite ; 
 int /*<<< orphan*/ * ext4_dio_get_block_unwritten_async ; 
 int /*<<< orphan*/ * ext4_dio_get_block_unwritten_sync ; 
 int /*<<< orphan*/  ext4_end_io_dio ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 int /*<<< orphan*/  ext4_update_i_disksize (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  inode_dio_begin (struct inode*) ; 
 int /*<<< orphan*/  inode_dio_end (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ is_sync_kiocb (struct kiocb*) ; 
 scalar_t__ round_down (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ext4_direct_IO_write(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	struct ext4_inode_info *ei = EXT4_I(inode);
	ssize_t ret;
	loff_t offset = iocb->ki_pos;
	size_t count = iov_iter_count(iter);
	int overwrite = 0;
	get_block_t *get_block_func = NULL;
	int dio_flags = 0;
	loff_t final_size = offset + count;
	int orphan = 0;
	handle_t *handle;

	if (final_size > inode->i_size || final_size > ei->i_disksize) {
		/* Credits for sb + inode write */
		handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			goto out;
		}
		ret = ext4_orphan_add(handle, inode);
		if (ret) {
			ext4_journal_stop(handle);
			goto out;
		}
		orphan = 1;
		ext4_update_i_disksize(inode, inode->i_size);
		ext4_journal_stop(handle);
	}

	BUG_ON(iocb->private == NULL);

	/*
	 * Make all waiters for direct IO properly wait also for extent
	 * conversion. This also disallows race between truncate() and
	 * overwrite DIO as i_dio_count needs to be incremented under i_mutex.
	 */
	inode_dio_begin(inode);

	/* If we do a overwrite dio, i_mutex locking can be released */
	overwrite = *((int *)iocb->private);

	if (overwrite)
		inode_unlock(inode);

	/*
	 * For extent mapped files we could direct write to holes and fallocate.
	 *
	 * Allocated blocks to fill the hole are marked as unwritten to prevent
	 * parallel buffered read to expose the stale data before DIO complete
	 * the data IO.
	 *
	 * As to previously fallocated extents, ext4 get_block will just simply
	 * mark the buffer mapped but still keep the extents unwritten.
	 *
	 * For non AIO case, we will convert those unwritten extents to written
	 * after return back from blockdev_direct_IO. That way we save us from
	 * allocating io_end structure and also the overhead of offloading
	 * the extent convertion to a workqueue.
	 *
	 * For async DIO, the conversion needs to be deferred when the
	 * IO is completed. The ext4 end_io callback function will be
	 * called to take care of the conversion work.  Here for async
	 * case, we allocate an io_end structure to hook to the iocb.
	 */
	iocb->private = NULL;
	if (overwrite)
		get_block_func = ext4_dio_get_block_overwrite;
	else if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS) ||
		   round_down(offset, i_blocksize(inode)) >= inode->i_size) {
		get_block_func = ext4_dio_get_block;
		dio_flags = DIO_LOCKING | DIO_SKIP_HOLES;
	} else if (is_sync_kiocb(iocb)) {
		get_block_func = ext4_dio_get_block_unwritten_sync;
		dio_flags = DIO_LOCKING;
	} else {
		get_block_func = ext4_dio_get_block_unwritten_async;
		dio_flags = DIO_LOCKING;
	}
	ret = __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev, iter,
				   get_block_func, ext4_end_io_dio, NULL,
				   dio_flags);

	if (ret > 0 && !overwrite && ext4_test_inode_state(inode,
						EXT4_STATE_DIO_UNWRITTEN)) {
		int err;
		/*
		 * for non AIO case, since the IO is already
		 * completed, we could do the conversion right here
		 */
		err = ext4_convert_unwritten_extents(NULL, inode,
						     offset, ret);
		if (err < 0)
			ret = err;
		ext4_clear_inode_state(inode, EXT4_STATE_DIO_UNWRITTEN);
	}

	inode_dio_end(inode);
	/* take i_mutex locking again if we do a ovewrite dio */
	if (overwrite)
		inode_lock(inode);

	if (ret < 0 && final_size > inode->i_size)
		ext4_truncate_failed_write(inode);

	/* Handle extending of i_size after direct IO write */
	if (orphan) {
		int err;

		/* Credits for sb + inode write */
		handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
		if (IS_ERR(handle)) {
			/*
			 * We wrote the data but cannot extend
			 * i_size. Bail out. In async io case, we do
			 * not return error here because we have
			 * already submmitted the corresponding
			 * bio. Returning error here makes the caller
			 * think that this IO is done and failed
			 * resulting in race with bio's completion
			 * handler.
			 */
			if (!ret)
				ret = PTR_ERR(handle);
			if (inode->i_nlink)
				ext4_orphan_del(NULL, inode);

			goto out;
		}
		if (inode->i_nlink)
			ext4_orphan_del(handle, inode);
		if (ret > 0) {
			loff_t end = offset + ret;
			if (end > inode->i_size || end > ei->i_disksize) {
				ext4_update_i_disksize(inode, end);
				if (end > inode->i_size)
					i_size_write(inode, end);
				/*
				 * We're going to return a positive `ret'
				 * here due to non-zero-length I/O, so there's
				 * no way of reporting error returns from
				 * ext4_mark_inode_dirty() to userspace.  So
				 * ignore it.
				 */
				ext4_mark_inode_dirty(handle, inode);
			}
		}
		err = ext4_journal_stop(handle);
		if (ret == 0)
			ret = err;
	}
out:
	return ret;
}