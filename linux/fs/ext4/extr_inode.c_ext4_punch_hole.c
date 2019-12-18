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
struct super_block {int s_blocksize; } ;
struct inode {int i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; struct address_space* i_mapping; struct super_block* i_sb; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mmap_sem; int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_HT_TRUNCATE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 unsigned int ext4_blocks_for_truncate (struct inode*) ; 
 int ext4_break_layouts (struct inode*) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_convert_inline_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int ext4_es_remove_extent (struct inode*,int,int) ; 
 int ext4_ext_remove_space (struct inode*,int,int) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int ext4_ind_remove_space (int /*<<< orphan*/ *,struct inode*,int,int) ; 
 int ext4_inode_attach_jinode (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (struct super_block*,int) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_update_disksize_before_punch (struct inode*,int,int) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 unsigned int ext4_writepage_trans_blocks (struct inode*) ; 
 int ext4_zero_partial_blocks (int /*<<< orphan*/ *,struct inode*,int,int) ; 
 int filemap_write_and_wait_range (struct address_space*,int,int) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 
 int round_down (int,int) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  trace_ext4_punch_hole (struct inode*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_punch_hole(struct inode *inode, loff_t offset, loff_t length)
{
	struct super_block *sb = inode->i_sb;
	ext4_lblk_t first_block, stop_block;
	struct address_space *mapping = inode->i_mapping;
	loff_t first_block_offset, last_block_offset;
	handle_t *handle;
	unsigned int credits;
	int ret = 0;

	if (!S_ISREG(inode->i_mode))
		return -EOPNOTSUPP;

	trace_ext4_punch_hole(inode, offset, length, 0);

	ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	if (ext4_has_inline_data(inode)) {
		down_write(&EXT4_I(inode)->i_mmap_sem);
		ret = ext4_convert_inline_data(inode);
		up_write(&EXT4_I(inode)->i_mmap_sem);
		if (ret)
			return ret;
	}

	/*
	 * Write out all dirty pages to avoid race conditions
	 * Then release them.
	 */
	if (mapping_tagged(mapping, PAGECACHE_TAG_DIRTY)) {
		ret = filemap_write_and_wait_range(mapping, offset,
						   offset + length - 1);
		if (ret)
			return ret;
	}

	inode_lock(inode);

	/* No need to punch hole beyond i_size */
	if (offset >= inode->i_size)
		goto out_mutex;

	/*
	 * If the hole extends beyond i_size, set the hole
	 * to end after the page that contains i_size
	 */
	if (offset + length > inode->i_size) {
		length = inode->i_size +
		   PAGE_SIZE - (inode->i_size & (PAGE_SIZE - 1)) -
		   offset;
	}

	if (offset & (sb->s_blocksize - 1) ||
	    (offset + length) & (sb->s_blocksize - 1)) {
		/*
		 * Attach jinode to inode for jbd2 if we do any zeroing of
		 * partial block
		 */
		ret = ext4_inode_attach_jinode(inode);
		if (ret < 0)
			goto out_mutex;

	}

	/* Wait all existing dio workers, newcomers will block on i_mutex */
	inode_dio_wait(inode);

	/*
	 * Prevent page faults from reinstantiating pages we have released from
	 * page cache.
	 */
	down_write(&EXT4_I(inode)->i_mmap_sem);

	ret = ext4_break_layouts(inode);
	if (ret)
		goto out_dio;

	first_block_offset = round_up(offset, sb->s_blocksize);
	last_block_offset = round_down((offset + length), sb->s_blocksize) - 1;

	/* Now release the pages and zero block aligned part of pages*/
	if (last_block_offset > first_block_offset) {
		ret = ext4_update_disksize_before_punch(inode, offset, length);
		if (ret)
			goto out_dio;
		truncate_pagecache_range(inode, first_block_offset,
					 last_block_offset);
	}

	if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		credits = ext4_writepage_trans_blocks(inode);
	else
		credits = ext4_blocks_for_truncate(inode);
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		ext4_std_error(sb, ret);
		goto out_dio;
	}

	ret = ext4_zero_partial_blocks(handle, inode, offset,
				       length);
	if (ret)
		goto out_stop;

	first_block = (offset + sb->s_blocksize - 1) >>
		EXT4_BLOCK_SIZE_BITS(sb);
	stop_block = (offset + length) >> EXT4_BLOCK_SIZE_BITS(sb);

	/* If there are blocks to remove, do it */
	if (stop_block > first_block) {

		down_write(&EXT4_I(inode)->i_data_sem);
		ext4_discard_preallocations(inode);

		ret = ext4_es_remove_extent(inode, first_block,
					    stop_block - first_block);
		if (ret) {
			up_write(&EXT4_I(inode)->i_data_sem);
			goto out_stop;
		}

		if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
			ret = ext4_ext_remove_space(inode, first_block,
						    stop_block - 1);
		else
			ret = ext4_ind_remove_space(handle, inode, first_block,
						    stop_block);

		up_write(&EXT4_I(inode)->i_data_sem);
	}
	if (IS_SYNC(inode))
		ext4_handle_sync(handle);

	inode->i_mtime = inode->i_ctime = current_time(inode);
	ext4_mark_inode_dirty(handle, inode);
	if (ret >= 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);
out_stop:
	ext4_journal_stop(handle);
out_dio:
	up_write(&EXT4_I(inode)->i_mmap_sem);
out_mutex:
	inode_unlock(inode);
	return ret;
}