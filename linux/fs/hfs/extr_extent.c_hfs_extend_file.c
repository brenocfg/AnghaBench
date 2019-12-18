#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
typedef  int /*<<< orphan*/  hfs_extent_rec ;
struct TYPE_9__ {scalar_t__ alloc_blocks; scalar_t__ first_blocks; scalar_t__ clump_blocks; scalar_t__ cached_start; int flags; scalar_t__ cached_blocks; TYPE_1__* cached_extents; int /*<<< orphan*/  extents_lock; TYPE_1__* first_extents; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {void* count; void* block; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  EXTENT ; 
 scalar_t__ HFS_FIRSTUSER_CNID ; 
 int /*<<< orphan*/  HFS_FLG_ALT_MDB_DIRTY ; 
 int HFS_FLG_EXT_DIRTY ; 
 int HFS_FLG_EXT_NEW ; 
 int /*<<< orphan*/  HFS_FLG_MDB_DIRTY ; 
 TYPE_6__* HFS_I (struct inode*) ; 
 TYPE_5__* HFS_SB (struct super_block*) ; 
 void* cpu_to_be16 (scalar_t__) ; 
 int hfs_add_extent (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hfs_dump_extent (TYPE_1__*) ; 
 scalar_t__ hfs_ext_lastblock (TYPE_1__*) ; 
 int hfs_ext_read_extent (struct inode*,scalar_t__) ; 
 int hfs_ext_write_extent (struct inode*) ; 
 int /*<<< orphan*/  hfs_mark_mdb_dirty (struct super_block*) ; 
 scalar_t__ hfs_vbm_search_free (struct super_block*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hfs_extend_file(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	u32 start, len, goal;
	int res;

	mutex_lock(&HFS_I(inode)->extents_lock);
	if (HFS_I(inode)->alloc_blocks == HFS_I(inode)->first_blocks)
		goal = hfs_ext_lastblock(HFS_I(inode)->first_extents);
	else {
		res = hfs_ext_read_extent(inode, HFS_I(inode)->alloc_blocks);
		if (res)
			goto out;
		goal = hfs_ext_lastblock(HFS_I(inode)->cached_extents);
	}

	len = HFS_I(inode)->clump_blocks;
	start = hfs_vbm_search_free(sb, goal, &len);
	if (!len) {
		res = -ENOSPC;
		goto out;
	}

	hfs_dbg(EXTENT, "extend %lu: %u,%u\n", inode->i_ino, start, len);
	if (HFS_I(inode)->alloc_blocks == HFS_I(inode)->first_blocks) {
		if (!HFS_I(inode)->first_blocks) {
			hfs_dbg(EXTENT, "first extents\n");
			/* no extents yet */
			HFS_I(inode)->first_extents[0].block = cpu_to_be16(start);
			HFS_I(inode)->first_extents[0].count = cpu_to_be16(len);
			res = 0;
		} else {
			/* try to append to extents in inode */
			res = hfs_add_extent(HFS_I(inode)->first_extents,
					     HFS_I(inode)->alloc_blocks,
					     start, len);
			if (res == -ENOSPC)
				goto insert_extent;
		}
		if (!res) {
			hfs_dump_extent(HFS_I(inode)->first_extents);
			HFS_I(inode)->first_blocks += len;
		}
	} else {
		res = hfs_add_extent(HFS_I(inode)->cached_extents,
				     HFS_I(inode)->alloc_blocks -
				     HFS_I(inode)->cached_start,
				     start, len);
		if (!res) {
			hfs_dump_extent(HFS_I(inode)->cached_extents);
			HFS_I(inode)->flags |= HFS_FLG_EXT_DIRTY;
			HFS_I(inode)->cached_blocks += len;
		} else if (res == -ENOSPC)
			goto insert_extent;
	}
out:
	mutex_unlock(&HFS_I(inode)->extents_lock);
	if (!res) {
		HFS_I(inode)->alloc_blocks += len;
		mark_inode_dirty(inode);
		if (inode->i_ino < HFS_FIRSTUSER_CNID)
			set_bit(HFS_FLG_ALT_MDB_DIRTY, &HFS_SB(sb)->flags);
		set_bit(HFS_FLG_MDB_DIRTY, &HFS_SB(sb)->flags);
		hfs_mark_mdb_dirty(sb);
	}
	return res;

insert_extent:
	hfs_dbg(EXTENT, "insert new extent\n");
	res = hfs_ext_write_extent(inode);
	if (res)
		goto out;

	memset(HFS_I(inode)->cached_extents, 0, sizeof(hfs_extent_rec));
	HFS_I(inode)->cached_extents[0].block = cpu_to_be16(start);
	HFS_I(inode)->cached_extents[0].count = cpu_to_be16(len);
	hfs_dump_extent(HFS_I(inode)->cached_extents);
	HFS_I(inode)->flags |= HFS_FLG_EXT_DIRTY|HFS_FLG_EXT_NEW;
	HFS_I(inode)->cached_start = HFS_I(inode)->alloc_blocks;
	HFS_I(inode)->cached_blocks = len;

	res = 0;
	goto out;
}