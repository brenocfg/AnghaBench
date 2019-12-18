#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct hfsplus_sb_info {int total_blocks; int free_blocks; TYPE_1__* alloc_file; } ;
struct hfsplus_inode_info {scalar_t__ alloc_blocks; scalar_t__ first_blocks; scalar_t__ clump_blocks; scalar_t__ cached_start; int extent_state; scalar_t__ cached_blocks; TYPE_2__* cached_extents; int /*<<< orphan*/  extents_lock; TYPE_2__* first_extents; } ;
typedef  int /*<<< orphan*/  hfsplus_extent_rec ;
struct TYPE_7__ {void* block_count; void* start_block; } ;
struct TYPE_6__ {int i_size; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  EXTENT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int HFSPLUS_EXT_DIRTY ; 
 int HFSPLUS_EXT_NEW ; 
 struct hfsplus_inode_info* HFSPLUS_I (struct inode*) ; 
 int /*<<< orphan*/  HFSPLUS_I_ALLOC_DIRTY ; 
 struct hfsplus_sb_info* HFSPLUS_SB (struct super_block*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int hfsplus_add_extent (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ hfsplus_block_allocate (struct super_block*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  hfsplus_dump_extent (TYPE_2__*) ; 
 scalar_t__ hfsplus_ext_lastblock (TYPE_2__*) ; 
 int hfsplus_ext_read_extent (struct inode*,scalar_t__) ; 
 int hfsplus_ext_write_extent_locked (struct inode*) ; 
 int /*<<< orphan*/  hfsplus_mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int sb_issue_zeroout (struct super_block*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int hfsplus_file_extend(struct inode *inode, bool zeroout)
{
	struct super_block *sb = inode->i_sb;
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
	u32 start, len, goal;
	int res;

	if (sbi->alloc_file->i_size * 8 <
	    sbi->total_blocks - sbi->free_blocks + 8) {
		/* extend alloc file */
		pr_err("extend alloc file! (%llu,%u,%u)\n",
		       sbi->alloc_file->i_size * 8,
		       sbi->total_blocks, sbi->free_blocks);
		return -ENOSPC;
	}

	mutex_lock(&hip->extents_lock);
	if (hip->alloc_blocks == hip->first_blocks)
		goal = hfsplus_ext_lastblock(hip->first_extents);
	else {
		res = hfsplus_ext_read_extent(inode, hip->alloc_blocks);
		if (res)
			goto out;
		goal = hfsplus_ext_lastblock(hip->cached_extents);
	}

	len = hip->clump_blocks;
	start = hfsplus_block_allocate(sb, sbi->total_blocks, goal, &len);
	if (start >= sbi->total_blocks) {
		start = hfsplus_block_allocate(sb, goal, 0, &len);
		if (start >= goal) {
			res = -ENOSPC;
			goto out;
		}
	}

	if (zeroout) {
		res = sb_issue_zeroout(sb, start, len, GFP_NOFS);
		if (res)
			goto out;
	}

	hfs_dbg(EXTENT, "extend %lu: %u,%u\n", inode->i_ino, start, len);

	if (hip->alloc_blocks <= hip->first_blocks) {
		if (!hip->first_blocks) {
			hfs_dbg(EXTENT, "first extents\n");
			/* no extents yet */
			hip->first_extents[0].start_block = cpu_to_be32(start);
			hip->first_extents[0].block_count = cpu_to_be32(len);
			res = 0;
		} else {
			/* try to append to extents in inode */
			res = hfsplus_add_extent(hip->first_extents,
						 hip->alloc_blocks,
						 start, len);
			if (res == -ENOSPC)
				goto insert_extent;
		}
		if (!res) {
			hfsplus_dump_extent(hip->first_extents);
			hip->first_blocks += len;
		}
	} else {
		res = hfsplus_add_extent(hip->cached_extents,
					 hip->alloc_blocks - hip->cached_start,
					 start, len);
		if (!res) {
			hfsplus_dump_extent(hip->cached_extents);
			hip->extent_state |= HFSPLUS_EXT_DIRTY;
			hip->cached_blocks += len;
		} else if (res == -ENOSPC)
			goto insert_extent;
	}
out:
	if (!res) {
		hip->alloc_blocks += len;
		mutex_unlock(&hip->extents_lock);
		hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ALLOC_DIRTY);
		return 0;
	}
	mutex_unlock(&hip->extents_lock);
	return res;

insert_extent:
	hfs_dbg(EXTENT, "insert new extent\n");
	res = hfsplus_ext_write_extent_locked(inode);
	if (res)
		goto out;

	memset(hip->cached_extents, 0, sizeof(hfsplus_extent_rec));
	hip->cached_extents[0].start_block = cpu_to_be32(start);
	hip->cached_extents[0].block_count = cpu_to_be32(len);
	hfsplus_dump_extent(hip->cached_extents);
	hip->extent_state |= HFSPLUS_EXT_DIRTY | HFSPLUS_EXT_NEW;
	hip->cached_start = hip->alloc_blocks;
	hip->cached_blocks = len;

	res = 0;
	goto out;
}