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
struct super_block {scalar_t__ s_maxbytes; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mapping; struct super_block* i_sb; int /*<<< orphan*/  i_mode; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; } ;
typedef  int loff_t ;
typedef  struct ext4_ext_path handle_t ;
typedef  unsigned int ext4_lblk_t ;
struct TYPE_2__ {int i_disksize; int /*<<< orphan*/  i_mmap_sem; int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 int EXT4_CLUSTER_SIZE (struct super_block*) ; 
 int EXT4_EXT_MARK_UNWRIT1 ; 
 int EXT4_EXT_MARK_UNWRIT2 ; 
 int EXT4_EX_NOCACHE ; 
 int EXT4_GET_BLOCKS_METADATA_NOFAIL ; 
 int EXT4_GET_BLOCKS_PRE_IO ; 
 int /*<<< orphan*/  EXT4_HT_TRUNCATE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 scalar_t__ EXT_MAX_BLOCKS ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  SHIFT_RIGHT ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int ext4_break_layouts (struct inode*) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int ext4_es_remove_extent (struct inode*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 unsigned int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_is_unwritten (struct ext4_extent*) ; 
 int ext4_ext_shift_extents (struct inode*,struct ext4_ext_path*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext4_force_commit (struct super_block*) ; 
 int /*<<< orphan*/  ext4_handle_sync (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_journal_start (struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_journal_stop (struct ext4_ext_path*) ; 
 int ext4_mark_inode_dirty (struct ext4_ext_path*,struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int ext4_split_extent_at (struct ext4_ext_path*,struct inode*,struct ext4_ext_path**,unsigned int,int,int) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_update_inode_fsync_trans (struct ext4_ext_path*,struct inode*,int) ; 
 unsigned int ext4_writepage_trans_blocks (struct inode*) ; 
 int ext_depth (struct inode*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int round_down (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_insert_range (struct inode*,int,int) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_insert_range(struct inode *inode, loff_t offset, loff_t len)
{
	struct super_block *sb = inode->i_sb;
	handle_t *handle;
	struct ext4_ext_path *path;
	struct ext4_extent *extent;
	ext4_lblk_t offset_lblk, len_lblk, ee_start_lblk = 0;
	unsigned int credits, ee_len;
	int ret = 0, depth, split_flag = 0;
	loff_t ioffset;

	/*
	 * We need to test this early because xfstests assumes that an
	 * insert range of (0, 1) will return EOPNOTSUPP if the file
	 * system does not support insert range.
	 */
	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		return -EOPNOTSUPP;

	/* Insert range works only on fs block size aligned offsets. */
	if (offset & (EXT4_CLUSTER_SIZE(sb) - 1) ||
			len & (EXT4_CLUSTER_SIZE(sb) - 1))
		return -EINVAL;

	if (!S_ISREG(inode->i_mode))
		return -EOPNOTSUPP;

	trace_ext4_insert_range(inode, offset, len);

	offset_lblk = offset >> EXT4_BLOCK_SIZE_BITS(sb);
	len_lblk = len >> EXT4_BLOCK_SIZE_BITS(sb);

	/* Call ext4_force_commit to flush all data in case of data=journal */
	if (ext4_should_journal_data(inode)) {
		ret = ext4_force_commit(inode->i_sb);
		if (ret)
			return ret;
	}

	inode_lock(inode);
	/* Currently just for extent based files */
	if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		ret = -EOPNOTSUPP;
		goto out_mutex;
	}

	/* Check for wrap through zero */
	if (inode->i_size + len > inode->i_sb->s_maxbytes) {
		ret = -EFBIG;
		goto out_mutex;
	}

	/* Offset should be less than i_size */
	if (offset >= i_size_read(inode)) {
		ret = -EINVAL;
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
	 * Need to round down to align start offset to page size boundary
	 * for page size > block size.
	 */
	ioffset = round_down(offset, PAGE_SIZE);
	/* Write out all dirty pages */
	ret = filemap_write_and_wait_range(inode->i_mapping, ioffset,
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

	/* Expand file to avoid data loss if there is error while shifting */
	inode->i_size += len;
	EXT4_I(inode)->i_disksize += len;
	inode->i_mtime = inode->i_ctime = current_time(inode);
	ret = ext4_mark_inode_dirty(handle, inode);
	if (ret)
		goto out_stop;

	down_write(&EXT4_I(inode)->i_data_sem);
	ext4_discard_preallocations(inode);

	path = ext4_find_extent(inode, offset_lblk, NULL, 0);
	if (IS_ERR(path)) {
		up_write(&EXT4_I(inode)->i_data_sem);
		goto out_stop;
	}

	depth = ext_depth(inode);
	extent = path[depth].p_ext;
	if (extent) {
		ee_start_lblk = le32_to_cpu(extent->ee_block);
		ee_len = ext4_ext_get_actual_len(extent);

		/*
		 * If offset_lblk is not the starting block of extent, split
		 * the extent @offset_lblk
		 */
		if ((offset_lblk > ee_start_lblk) &&
				(offset_lblk < (ee_start_lblk + ee_len))) {
			if (ext4_ext_is_unwritten(extent))
				split_flag = EXT4_EXT_MARK_UNWRIT1 |
					EXT4_EXT_MARK_UNWRIT2;
			ret = ext4_split_extent_at(handle, inode, &path,
					offset_lblk, split_flag,
					EXT4_EX_NOCACHE |
					EXT4_GET_BLOCKS_PRE_IO |
					EXT4_GET_BLOCKS_METADATA_NOFAIL);
		}

		ext4_ext_drop_refs(path);
		kfree(path);
		if (ret < 0) {
			up_write(&EXT4_I(inode)->i_data_sem);
			goto out_stop;
		}
	} else {
		ext4_ext_drop_refs(path);
		kfree(path);
	}

	ret = ext4_es_remove_extent(inode, offset_lblk,
			EXT_MAX_BLOCKS - offset_lblk);
	if (ret) {
		up_write(&EXT4_I(inode)->i_data_sem);
		goto out_stop;
	}

	/*
	 * if offset_lblk lies in a hole which is at start of file, use
	 * ee_start_lblk to shift extents
	 */
	ret = ext4_ext_shift_extents(inode, handle,
		ee_start_lblk > offset_lblk ? ee_start_lblk : offset_lblk,
		len_lblk, SHIFT_RIGHT);

	up_write(&EXT4_I(inode)->i_data_sem);
	if (IS_SYNC(inode))
		ext4_handle_sync(handle);
	if (ret >= 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);

out_stop:
	ext4_journal_stop(handle);
out_mmap:
	up_write(&EXT4_I(inode)->i_mmap_sem);
out_mutex:
	inode_unlock(inode);
	return ret;
}