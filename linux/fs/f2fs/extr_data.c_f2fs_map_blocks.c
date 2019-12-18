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
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_map_blocks {unsigned int m_len; int m_flags; unsigned int m_lblk; scalar_t__ m_pblk; unsigned int* m_next_extent; unsigned int* m_next_pgofs; scalar_t__ m_may_create; int /*<<< orphan*/  m_seg_type; } ;
struct extent_info {scalar_t__ blk; scalar_t__ fofs; scalar_t__ len; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dnode_of_data {unsigned int ofs_in_node; scalar_t__ data_blkaddr; int /*<<< orphan*/  node_changed; int /*<<< orphan*/  node_page; int /*<<< orphan*/  inode; } ;
typedef  unsigned int pgoff_t ;
typedef  scalar_t__ block_t ;
typedef  scalar_t__ blkcnt_t ;

/* Variables and functions */
 unsigned int ADDRS_PER_PAGE (int /*<<< orphan*/ ,struct inode*) ; 
 int ALLOC_NODE ; 
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 int ENOENT ; 
 int ENOSPC ; 
 int F2FS_GET_BLOCK_BMAP ; 
 int F2FS_GET_BLOCK_DIO ; 
 int F2FS_GET_BLOCK_FIEMAP ; 
 int F2FS_GET_BLOCK_PRECACHE ; 
 int F2FS_GET_BLOCK_PRE_AIO ; 
 int F2FS_GET_BLOCK_PRE_DIO ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int F2FS_MAP_MAPPED ; 
 int F2FS_MAP_NEW ; 
 int F2FS_MAP_UNWRITTEN ; 
 int /*<<< orphan*/  FI_APPEND_WRITE ; 
 int /*<<< orphan*/  LFS ; 
 int LOOKUP_NODE ; 
 scalar_t__ NEW_ADDR ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __allocate_data_block (struct dnode_of_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __do_map_lock (struct f2fs_sb_info*,int,int) ; 
 scalar_t__ __is_valid_data_blkaddr (scalar_t__) ; 
 scalar_t__ datablock_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,unsigned int,int) ; 
 void* f2fs_get_next_page_offset (struct dnode_of_data*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_lookup_extent_cache (struct inode*,unsigned int,struct extent_info*) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int f2fs_reserve_new_blocks (struct dnode_of_data*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_update_extent_cache_range (struct dnode_of_data*,unsigned int,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  f2fs_wait_on_block_writeback_range (struct inode*,scalar_t__,unsigned int) ; 
 unsigned int min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_map_blocks (struct inode*,struct f2fs_map_blocks*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int f2fs_map_blocks(struct inode *inode, struct f2fs_map_blocks *map,
						int create, int flag)
{
	unsigned int maxblocks = map->m_len;
	struct dnode_of_data dn;
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int mode = map->m_may_create ? ALLOC_NODE : LOOKUP_NODE;
	pgoff_t pgofs, end_offset, end;
	int err = 0, ofs = 1;
	unsigned int ofs_in_node, last_ofs_in_node;
	blkcnt_t prealloc;
	struct extent_info ei = {0,0,0};
	block_t blkaddr;
	unsigned int start_pgofs;

	if (!maxblocks)
		return 0;

	map->m_len = 0;
	map->m_flags = 0;

	/* it only supports block size == page size */
	pgofs =	(pgoff_t)map->m_lblk;
	end = pgofs + maxblocks;

	if (!create && f2fs_lookup_extent_cache(inode, pgofs, &ei)) {
		if (test_opt(sbi, LFS) && flag == F2FS_GET_BLOCK_DIO &&
							map->m_may_create)
			goto next_dnode;

		map->m_pblk = ei.blk + pgofs - ei.fofs;
		map->m_len = min((pgoff_t)maxblocks, ei.fofs + ei.len - pgofs);
		map->m_flags = F2FS_MAP_MAPPED;
		if (map->m_next_extent)
			*map->m_next_extent = pgofs + map->m_len;

		/* for hardware encryption, but to avoid potential issue in future */
		if (flag == F2FS_GET_BLOCK_DIO)
			f2fs_wait_on_block_writeback_range(inode,
						map->m_pblk, map->m_len);
		goto out;
	}

next_dnode:
	if (map->m_may_create)
		__do_map_lock(sbi, flag, true);

	/* When reading holes, we need its node page */
	set_new_dnode(&dn, inode, NULL, NULL, 0);
	err = f2fs_get_dnode_of_data(&dn, pgofs, mode);
	if (err) {
		if (flag == F2FS_GET_BLOCK_BMAP)
			map->m_pblk = 0;
		if (err == -ENOENT) {
			err = 0;
			if (map->m_next_pgofs)
				*map->m_next_pgofs =
					f2fs_get_next_page_offset(&dn, pgofs);
			if (map->m_next_extent)
				*map->m_next_extent =
					f2fs_get_next_page_offset(&dn, pgofs);
		}
		goto unlock_out;
	}

	start_pgofs = pgofs;
	prealloc = 0;
	last_ofs_in_node = ofs_in_node = dn.ofs_in_node;
	end_offset = ADDRS_PER_PAGE(dn.node_page, inode);

next_block:
	blkaddr = datablock_addr(dn.inode, dn.node_page, dn.ofs_in_node);

	if (__is_valid_data_blkaddr(blkaddr) &&
		!f2fs_is_valid_blkaddr(sbi, blkaddr, DATA_GENERIC_ENHANCE)) {
		err = -EFSCORRUPTED;
		goto sync_out;
	}

	if (__is_valid_data_blkaddr(blkaddr)) {
		/* use out-place-update for driect IO under LFS mode */
		if (test_opt(sbi, LFS) && flag == F2FS_GET_BLOCK_DIO &&
							map->m_may_create) {
			err = __allocate_data_block(&dn, map->m_seg_type);
			if (err)
				goto sync_out;
			blkaddr = dn.data_blkaddr;
			set_inode_flag(inode, FI_APPEND_WRITE);
		}
	} else {
		if (create) {
			if (unlikely(f2fs_cp_error(sbi))) {
				err = -EIO;
				goto sync_out;
			}
			if (flag == F2FS_GET_BLOCK_PRE_AIO) {
				if (blkaddr == NULL_ADDR) {
					prealloc++;
					last_ofs_in_node = dn.ofs_in_node;
				}
			} else {
				WARN_ON(flag != F2FS_GET_BLOCK_PRE_DIO &&
					flag != F2FS_GET_BLOCK_DIO);
				err = __allocate_data_block(&dn,
							map->m_seg_type);
				if (!err)
					set_inode_flag(inode, FI_APPEND_WRITE);
			}
			if (err)
				goto sync_out;
			map->m_flags |= F2FS_MAP_NEW;
			blkaddr = dn.data_blkaddr;
		} else {
			if (flag == F2FS_GET_BLOCK_BMAP) {
				map->m_pblk = 0;
				goto sync_out;
			}
			if (flag == F2FS_GET_BLOCK_PRECACHE)
				goto sync_out;
			if (flag == F2FS_GET_BLOCK_FIEMAP &&
						blkaddr == NULL_ADDR) {
				if (map->m_next_pgofs)
					*map->m_next_pgofs = pgofs + 1;
				goto sync_out;
			}
			if (flag != F2FS_GET_BLOCK_FIEMAP) {
				/* for defragment case */
				if (map->m_next_pgofs)
					*map->m_next_pgofs = pgofs + 1;
				goto sync_out;
			}
		}
	}

	if (flag == F2FS_GET_BLOCK_PRE_AIO)
		goto skip;

	if (map->m_len == 0) {
		/* preallocated unwritten block should be mapped for fiemap. */
		if (blkaddr == NEW_ADDR)
			map->m_flags |= F2FS_MAP_UNWRITTEN;
		map->m_flags |= F2FS_MAP_MAPPED;

		map->m_pblk = blkaddr;
		map->m_len = 1;
	} else if ((map->m_pblk != NEW_ADDR &&
			blkaddr == (map->m_pblk + ofs)) ||
			(map->m_pblk == NEW_ADDR && blkaddr == NEW_ADDR) ||
			flag == F2FS_GET_BLOCK_PRE_DIO) {
		ofs++;
		map->m_len++;
	} else {
		goto sync_out;
	}

skip:
	dn.ofs_in_node++;
	pgofs++;

	/* preallocate blocks in batch for one dnode page */
	if (flag == F2FS_GET_BLOCK_PRE_AIO &&
			(pgofs == end || dn.ofs_in_node == end_offset)) {

		dn.ofs_in_node = ofs_in_node;
		err = f2fs_reserve_new_blocks(&dn, prealloc);
		if (err)
			goto sync_out;

		map->m_len += dn.ofs_in_node - ofs_in_node;
		if (prealloc && dn.ofs_in_node != last_ofs_in_node + 1) {
			err = -ENOSPC;
			goto sync_out;
		}
		dn.ofs_in_node = end_offset;
	}

	if (pgofs >= end)
		goto sync_out;
	else if (dn.ofs_in_node < end_offset)
		goto next_block;

	if (flag == F2FS_GET_BLOCK_PRECACHE) {
		if (map->m_flags & F2FS_MAP_MAPPED) {
			unsigned int ofs = start_pgofs - map->m_lblk;

			f2fs_update_extent_cache_range(&dn,
				start_pgofs, map->m_pblk + ofs,
				map->m_len - ofs);
		}
	}

	f2fs_put_dnode(&dn);

	if (map->m_may_create) {
		__do_map_lock(sbi, flag, false);
		f2fs_balance_fs(sbi, dn.node_changed);
	}
	goto next_dnode;

sync_out:

	/* for hardware encryption, but to avoid potential issue in future */
	if (flag == F2FS_GET_BLOCK_DIO && map->m_flags & F2FS_MAP_MAPPED)
		f2fs_wait_on_block_writeback_range(inode,
						map->m_pblk, map->m_len);

	if (flag == F2FS_GET_BLOCK_PRECACHE) {
		if (map->m_flags & F2FS_MAP_MAPPED) {
			unsigned int ofs = start_pgofs - map->m_lblk;

			f2fs_update_extent_cache_range(&dn,
				start_pgofs, map->m_pblk + ofs,
				map->m_len - ofs);
		}
		if (map->m_next_extent)
			*map->m_next_extent = pgofs + 1;
	}
	f2fs_put_dnode(&dn);
unlock_out:
	if (map->m_may_create) {
		__do_map_lock(sbi, flag, false);
		f2fs_balance_fs(sbi, dn.node_changed);
	}
out:
	trace_f2fs_map_blocks(inode, map, err);
	return err;
}