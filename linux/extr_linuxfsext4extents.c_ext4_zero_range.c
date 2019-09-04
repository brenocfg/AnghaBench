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
struct inode {unsigned int i_blkbits; void* i_ctime; void* i_mtime; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {int f_flags; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned int ext4_lblk_t ;
struct TYPE_2__ {int i_disksize; int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 long EINVAL ; 
 int EOPNOTSUPP ; 
 int EXT4_EX_NOCACHE ; 
 int EXT4_GET_BLOCKS_CONVERT_UNWRITTEN ; 
 int EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT ; 
 int EXT4_GET_BLOCKS_KEEP_SIZE ; 
 int /*<<< orphan*/  EXT4_HT_MISC ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EOFBLOCKS ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int FALLOC_FL_KEEP_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int O_SYNC ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 void* current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int ext4_alloc_file_blocks (struct file*,unsigned int,unsigned int,int,int) ; 
 int ext4_break_layouts (struct inode*) ; 
 int ext4_ext_index_trans_blocks (struct inode*,int) ; 
 int ext4_force_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_update_disksize_before_punch (struct inode*,int,int) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  ext4_update_inode_size (struct inode*,int) ; 
 int ext4_zero_partial_blocks (int /*<<< orphan*/ *,struct inode*,int,int) ; 
 struct inode* file_inode (struct file*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int inode_newsize_ok (struct inode*,int) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 unsigned int round_down (int,int) ; 
 unsigned int round_up (int,int) ; 
 int /*<<< orphan*/  trace_ext4_zero_range (struct inode*,int,int,int) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long ext4_zero_range(struct file *file, loff_t offset,
			    loff_t len, int mode)
{
	struct inode *inode = file_inode(file);
	handle_t *handle = NULL;
	unsigned int max_blocks;
	loff_t new_size = 0;
	int ret = 0;
	int flags;
	int credits;
	int partial_begin, partial_end;
	loff_t start, end;
	ext4_lblk_t lblk;
	unsigned int blkbits = inode->i_blkbits;

	trace_ext4_zero_range(inode, offset, len, mode);

	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	/* Call ext4_force_commit to flush all data in case of data=journal. */
	if (ext4_should_journal_data(inode)) {
		ret = ext4_force_commit(inode->i_sb);
		if (ret)
			return ret;
	}

	/*
	 * Round up offset. This is not fallocate, we neet to zero out
	 * blocks, so convert interior block aligned part of the range to
	 * unwritten and possibly manually zero out unaligned parts of the
	 * range.
	 */
	start = round_up(offset, 1 << blkbits);
	end = round_down((offset + len), 1 << blkbits);

	if (start < offset || end > offset + len)
		return -EINVAL;
	partial_begin = offset & ((1 << blkbits) - 1);
	partial_end = (offset + len) & ((1 << blkbits) - 1);

	lblk = start >> blkbits;
	max_blocks = (end >> blkbits);
	if (max_blocks < lblk)
		max_blocks = 0;
	else
		max_blocks -= lblk;

	inode_lock(inode);

	/*
	 * Indirect files do not support unwritten extnets
	 */
	if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) {
		ret = -EOPNOTSUPP;
		goto out_mutex;
	}

	if (!(mode & FALLOC_FL_KEEP_SIZE) &&
	    (offset + len > i_size_read(inode) ||
	     offset + len > EXT4_I(inode)->i_disksize)) {
		new_size = offset + len;
		ret = inode_newsize_ok(inode, new_size);
		if (ret)
			goto out_mutex;
	}

	flags = EXT4_GET_BLOCKS_CREATE_UNWRIT_EXT;
	if (mode & FALLOC_FL_KEEP_SIZE)
		flags |= EXT4_GET_BLOCKS_KEEP_SIZE;

	/* Wait all existing dio workers, newcomers will block on i_mutex */
	inode_dio_wait(inode);

	/* Preallocate the range including the unaligned edges */
	if (partial_begin || partial_end) {
		ret = ext4_alloc_file_blocks(file,
				round_down(offset, 1 << blkbits) >> blkbits,
				(round_up((offset + len), 1 << blkbits) -
				 round_down(offset, 1 << blkbits)) >> blkbits,
				new_size, flags);
		if (ret)
			goto out_mutex;

	}

	/* Zero range excluding the unaligned edges */
	if (max_blocks > 0) {
		flags |= (EXT4_GET_BLOCKS_CONVERT_UNWRITTEN |
			  EXT4_EX_NOCACHE);

		/*
		 * Prevent page faults from reinstantiating pages we have
		 * released from page cache.
		 */
		down_write(&EXT4_I(inode)->i_mmap_sem);

		ret = ext4_break_layouts(inode);
		if (ret) {
			up_write(&EXT4_I(inode)->i_mmap_sem);
			goto out_mutex;
		}

		ret = ext4_update_disksize_before_punch(inode, offset, len);
		if (ret) {
			up_write(&EXT4_I(inode)->i_mmap_sem);
			goto out_mutex;
		}
		/* Now release the pages and zero block aligned part of pages */
		truncate_pagecache_range(inode, start, end - 1);
		inode->i_mtime = inode->i_ctime = current_time(inode);

		ret = ext4_alloc_file_blocks(file, lblk, max_blocks, new_size,
					     flags);
		up_write(&EXT4_I(inode)->i_mmap_sem);
		if (ret)
			goto out_mutex;
	}
	if (!partial_begin && !partial_end)
		goto out_mutex;

	/*
	 * In worst case we have to writeout two nonadjacent unwritten
	 * blocks and update the inode
	 */
	credits = (2 * ext4_ext_index_trans_blocks(inode, 2)) + 1;
	if (ext4_should_journal_data(inode))
		credits += 2;
	handle = ext4_journal_start(inode, EXT4_HT_MISC, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		ext4_std_error(inode->i_sb, ret);
		goto out_mutex;
	}

	inode->i_mtime = inode->i_ctime = current_time(inode);
	if (new_size) {
		ext4_update_inode_size(inode, new_size);
	} else {
		/*
		* Mark that we allocate beyond EOF so the subsequent truncate
		* can proceed even if the new size is the same as i_size.
		*/
		if ((offset + len) > i_size_read(inode))
			ext4_set_inode_flag(inode, EXT4_INODE_EOFBLOCKS);
	}
	ext4_mark_inode_dirty(handle, inode);

	/* Zero out partial block at the edges of the range */
	ret = ext4_zero_partial_blocks(handle, inode, offset, len);
	if (ret >= 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);

	if (file->f_flags & O_SYNC)
		ext4_handle_sync(handle);

	ext4_journal_stop(handle);
out_mutex:
	inode_unlock(inode);
	return ret;
}