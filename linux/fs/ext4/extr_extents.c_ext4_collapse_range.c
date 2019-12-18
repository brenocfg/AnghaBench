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
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mapping; struct super_block* i_sb; int /*<<< orphan*/  i_mode; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_2__ {int i_disksize; int /*<<< orphan*/  i_mmap_sem; int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 int EXT4_CLUSTER_SIZE (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_HT_TRUNCATE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 scalar_t__ EXT_MAX_BLOCKS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int LLONG_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHIFT_LEFT ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int ext4_break_layouts (struct inode*) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int ext4_es_remove_extent (struct inode*,int,scalar_t__) ; 
 int ext4_ext_remove_space (struct inode*,int,int) ; 
 int ext4_ext_shift_extents (struct inode*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int ext4_force_commit (struct super_block*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 unsigned int ext4_writepage_trans_blocks (struct inode*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int,int) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_collapse_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_collapse_range(struct inode *inode, loff_t offset, loff_t len)
{
	struct super_block *sb = inode->i_sb;
	ext4_lblk_t punch_start, punch_stop;
	handle_t *handle;
	unsigned int credits;
	loff_t new_size, ioffset;
	int ret;

	/*
	 * We need to test this early because xfstests assumes that a
	 * collapse range of (0, 1) will return EOPNOTSUPP if the file
	 * system does not support collapse range.
	 */
	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		return -EOPNOTSUPP;

	/* Collapse range works only on fs block size aligned offsets. */
	if (offset & (EXT4_CLUSTER_SIZE(sb) - 1) ||
	    len & (EXT4_CLUSTER_SIZE(sb) - 1))
		return -EINVAL;

	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	trace_ext4_collapse_range(inode, offset, len);

	punch_start = offset >> EXT4_BLOCK_SIZE_BITS(sb);
	punch_stop = (offset + len) >> EXT4_BLOCK_SIZE_BITS(sb);

	/* Call ext4_force_commit to flush all data in case of data=journal. */
	if (ext4_should_journal_data(inode)) {
		ret = ext4_force_commit(inode->i_sb);
		if (ret)
			return ret;
	}

	inode_lock(inode);
	/*
	 * There is no need to overlap collapse range with EOF, in which case
	 * it is effectively a truncate operation
	 */
	if (offset + len >= i_size_read(inode)) {
		ret = -EINVAL;
		goto out_mutex;
	}

	/* Currently just for extent based files */
	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		ret = -EOPNOTSUPP;
		goto out_mutex;
	}

	/* Wait for existing dio to complete */
	inode_dio_wait(inode);

	/*
	 * Prevent page faults from reinstantiating pages we have released from
	 * page cache.
	 */
	down_write(&EXT4_I(inode)->i_mmap_sem);

	ret = ext4_break_layouts(inode);
	if (ret)
		goto out_mmap;

	/*
	 * Need to round down offset to be aligned with page size boundary
	 * for page size > block size.
	 */
	ioffset = round_down(offset, PAGE_SIZE);
	/*
	 * Write tail of the last page before removed range since it will get
	 * removed from the page cache below.
	 */
	ret = filemap_write_and_wait_range(inode->i_mapping, ioffset, offset);
	if (ret)
		goto out_mmap;
	/*
	 * Write data that will be shifted to preserve them when discarding
	 * page cache below. We are also protected from pages becoming dirty
	 * by i_mmap_sem.
	 */
	ret = filemap_write_and_wait_range(inode->i_mapping, offset + len,
					   LLONG_MAX);
	if (ret)
		goto out_mmap;
	truncate_pagecache(inode, ioffset);

	credits = ext4_writepage_trans_blocks(inode);
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out_mmap;
	}

	down_write(&EXT4_I(inode)->i_data_sem);
	ext4_discard_preallocations(inode);

	ret = ext4_es_remove_extent(inode, punch_start,
				    EXT_MAX_BLOCKS - punch_start);
	if (ret) {
		up_write(&EXT4_I(inode)->i_data_sem);
		goto out_stop;
	}

	ret = ext4_ext_remove_space(inode, punch_start, punch_stop - 1);
	if (ret) {
		up_write(&EXT4_I(inode)->i_data_sem);
		goto out_stop;
	}
	ext4_discard_preallocations(inode);

	ret = ext4_ext_shift_extents(inode, handle, punch_stop,
				     punch_stop - punch_start, SHIFT_LEFT);
	if (ret) {
		up_write(&EXT4_I(inode)->i_data_sem);
		goto out_stop;
	}

	new_size = i_size_read(inode) - len;
	i_size_write(inode, new_size);
	EXT4_I(inode)->i_disksize = new_size;

	up_write(&EXT4_I(inode)->i_data_sem);
	if (IS_SYNC(inode))
		ext4_handle_sync(handle);
	inode->i_mtime = inode->i_ctime = current_time(inode);
	ext4_mark_inode_dirty(handle, inode);
	ext4_update_inode_fsync_trans(handle, inode, 1);

out_stop:
	ext4_journal_stop(handle);
out_mmap:
	up_write(&EXT4_I(inode)->i_mmap_sem);
out_mutex:
	inode_unlock(inode);
	return ret;
}