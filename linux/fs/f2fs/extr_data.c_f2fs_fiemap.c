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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct fiemap_extent_info {int fi_flags; } ;
struct buffer_head {int b_blocknr; scalar_t__ b_size; } ;
typedef  int sector_t ;
typedef  int pgoff_t ;
struct TYPE_2__ {int max_file_blocks; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  F2FS_GET_BLOCK_FIEMAP ; 
 TYPE_1__* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FIEMAP_EXTENT_DATA_ENCRYPTED ; 
 int /*<<< orphan*/  FIEMAP_EXTENT_LAST ; 
 int /*<<< orphan*/  FIEMAP_EXTENT_UNWRITTEN ; 
 int FIEMAP_FLAG_CACHE ; 
 int FIEMAP_FLAG_SYNC ; 
 int FIEMAP_FLAG_XATTR ; 
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ blk_to_logical (struct inode*,int) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 int f2fs_inline_data_fiemap (struct inode*,struct fiemap_extent_info*,scalar_t__,scalar_t__) ; 
 int f2fs_precache_extents (struct inode*) ; 
 int f2fs_xattr_fiemap (struct inode*,struct fiemap_extent_info*) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int fiemap_check_flags (struct fiemap_extent_info*,int) ; 
 int fiemap_fill_next_extent (struct fiemap_extent_info*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int get_data_block (struct inode*,int,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ logical_to_blk (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct buffer_head*,int /*<<< orphan*/ ,int) ; 

int f2fs_fiemap(struct inode *inode, struct fiemap_extent_info *fieinfo,
		u64 start, u64 len)
{
	struct buffer_head map_bh;
	sector_t start_blk, last_blk;
	pgoff_t next_pgofs;
	u64 logical = 0, phys = 0, size = 0;
	u32 flags = 0;
	int ret = 0;

	if (fieinfo->fi_flags & FIEMAP_FLAG_CACHE) {
		ret = f2fs_precache_extents(inode);
		if (ret)
			return ret;
	}

	ret = fiemap_check_flags(fieinfo, FIEMAP_FLAG_SYNC | FIEMAP_FLAG_XATTR);
	if (ret)
		return ret;

	inode_lock(inode);

	if (fieinfo->fi_flags & FIEMAP_FLAG_XATTR) {
		ret = f2fs_xattr_fiemap(inode, fieinfo);
		goto out;
	}

	if (f2fs_has_inline_data(inode) || f2fs_has_inline_dentry(inode)) {
		ret = f2fs_inline_data_fiemap(inode, fieinfo, start, len);
		if (ret != -EAGAIN)
			goto out;
	}

	if (logical_to_blk(inode, len) == 0)
		len = blk_to_logical(inode, 1);

	start_blk = logical_to_blk(inode, start);
	last_blk = logical_to_blk(inode, start + len - 1);

next:
	memset(&map_bh, 0, sizeof(struct buffer_head));
	map_bh.b_size = len;

	ret = get_data_block(inode, start_blk, &map_bh, 0,
					F2FS_GET_BLOCK_FIEMAP, &next_pgofs);
	if (ret)
		goto out;

	/* HOLE */
	if (!buffer_mapped(&map_bh)) {
		start_blk = next_pgofs;

		if (blk_to_logical(inode, start_blk) < blk_to_logical(inode,
					F2FS_I_SB(inode)->max_file_blocks))
			goto prep_next;

		flags |= FIEMAP_EXTENT_LAST;
	}

	if (size) {
		if (IS_ENCRYPTED(inode))
			flags |= FIEMAP_EXTENT_DATA_ENCRYPTED;

		ret = fiemap_fill_next_extent(fieinfo, logical,
				phys, size, flags);
	}

	if (start_blk > last_blk || ret)
		goto out;

	logical = blk_to_logical(inode, start_blk);
	phys = blk_to_logical(inode, map_bh.b_blocknr);
	size = map_bh.b_size;
	flags = 0;
	if (buffer_unwritten(&map_bh))
		flags = FIEMAP_EXTENT_UNWRITTEN;

	start_blk += logical_to_blk(inode, size);

prep_next:
	cond_resched();
	if (fatal_signal_pending(current))
		ret = -EINTR;
	else
		goto next;
out:
	if (ret == 1)
		ret = 0;

	inode_unlock(inode);
	return ret;
}