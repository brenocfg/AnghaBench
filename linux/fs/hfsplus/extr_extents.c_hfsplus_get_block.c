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
typedef  int u32 ;
struct super_block {scalar_t__ s_blocksize; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct hfsplus_sb_info {int fs_shift; int blockoffset; } ;
struct hfsplus_inode_info {int fs_blocks; int alloc_blocks; int first_blocks; int extent_state; int cached_start; int /*<<< orphan*/  phys_size; int /*<<< orphan*/  extents_lock; int /*<<< orphan*/  cached_extents; int /*<<< orphan*/  first_extents; } ;
struct buffer_head {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXTENT ; 
 scalar_t__ HFSPLUS_EXT_CNID ; 
 int HFSPLUS_EXT_DIRTY ; 
 struct hfsplus_inode_info* HFSPLUS_I (struct inode*) ; 
 struct hfsplus_sb_info* HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,scalar_t__,long long,int) ; 
 int hfsplus_ext_find_block (int /*<<< orphan*/ ,int) ; 
 int hfsplus_ext_read_extent (struct inode*,int) ; 
 int hfsplus_file_extend (struct inode*,int) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,struct super_block*,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 

int hfsplus_get_block(struct inode *inode, sector_t iblock,
		      struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
	int res = -EIO;
	u32 ablock, dblock, mask;
	sector_t sector;
	int was_dirty = 0;

	/* Convert inode block to disk allocation block */
	ablock = iblock >> sbi->fs_shift;

	if (iblock >= hip->fs_blocks) {
		if (!create)
			return 0;
		if (iblock > hip->fs_blocks)
			return -EIO;
		if (ablock >= hip->alloc_blocks) {
			res = hfsplus_file_extend(inode, false);
			if (res)
				return res;
		}
	} else
		create = 0;

	if (ablock < hip->first_blocks) {
		dblock = hfsplus_ext_find_block(hip->first_extents, ablock);
		goto done;
	}

	if (inode->i_ino == HFSPLUS_EXT_CNID)
		return -EIO;

	mutex_lock(&hip->extents_lock);

	/*
	 * hfsplus_ext_read_extent will write out a cached extent into
	 * the extents btree.  In that case we may have to mark the inode
	 * dirty even for a pure read of an extent here.
	 */
	was_dirty = (hip->extent_state & HFSPLUS_EXT_DIRTY);
	res = hfsplus_ext_read_extent(inode, ablock);
	if (res) {
		mutex_unlock(&hip->extents_lock);
		return -EIO;
	}
	dblock = hfsplus_ext_find_block(hip->cached_extents,
					ablock - hip->cached_start);
	mutex_unlock(&hip->extents_lock);

done:
	hfs_dbg(EXTENT, "get_block(%lu): %llu - %u\n",
		inode->i_ino, (long long)iblock, dblock);

	mask = (1 << sbi->fs_shift) - 1;
	sector = ((sector_t)dblock << sbi->fs_shift) +
		  sbi->blockoffset + (iblock & mask);
	map_bh(bh_result, sb, sector);

	if (create) {
		set_buffer_new(bh_result);
		hip->phys_size += sb->s_blocksize;
		hip->fs_blocks++;
		inode_add_bytes(inode, sb->s_blocksize);
	}
	if (create || was_dirty)
		mark_inode_dirty(inode);
	return 0;
}