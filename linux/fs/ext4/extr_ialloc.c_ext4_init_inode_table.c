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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct ext4_sb_info {int s_itb_per_group; int /*<<< orphan*/  s_inodes_per_block; } ;
struct ext4_group_info {int /*<<< orphan*/  alloc_sem; } ;
struct ext4_group_desc {int bg_flags; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_BG_INODE_UNINIT ; 
 int /*<<< orphan*/  EXT4_BG_INODE_ZEROED ; 
 scalar_t__ EXT4_FIRST_INO (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_HT_MISC ; 
 scalar_t__ EXT4_INODES_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,scalar_t__,int,scalar_t__) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,struct buffer_head**) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_group_desc_csum_set (struct super_block*,scalar_t__,struct ext4_group_desc*) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_itable_unused_count (struct super_block*,struct ext4_group_desc*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ext4_journal_start_sb (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,scalar_t__) ; 
 int sb_issue_zeroout (struct super_block*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_init_inode_table(struct super_block *sb, ext4_group_t group,
				 int barrier)
{
	struct ext4_group_info *grp = ext4_get_group_info(sb, group);
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_group_desc *gdp = NULL;
	struct buffer_head *group_desc_bh;
	handle_t *handle;
	ext4_fsblk_t blk;
	int num, ret = 0, used_blks = 0;

	/* This should not happen, but just to be sure check this */
	if (sb_rdonly(sb)) {
		ret = 1;
		goto out;
	}

	gdp = ext4_get_group_desc(sb, group, &group_desc_bh);
	if (!gdp)
		goto out;

	/*
	 * We do not need to lock this, because we are the only one
	 * handling this flag.
	 */
	if (gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED))
		goto out;

	handle = ext4_journal_start_sb(sb, EXT4_HT_MISC, 1);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out;
	}

	down_write(&grp->alloc_sem);
	/*
	 * If inode bitmap was already initialized there may be some
	 * used inodes so we need to skip blocks with used inodes in
	 * inode table.
	 */
	if (!(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_UNINIT)))
		used_blks = DIV_ROUND_UP((EXT4_INODES_PER_GROUP(sb) -
			    ext4_itable_unused_count(sb, gdp)),
			    sbi->s_inodes_per_block);

	if ((used_blks < 0) || (used_blks > sbi->s_itb_per_group) ||
	    ((group == 0) && ((EXT4_INODES_PER_GROUP(sb) -
			       ext4_itable_unused_count(sb, gdp)) <
			      EXT4_FIRST_INO(sb)))) {
		ext4_error(sb, "Something is wrong with group %u: "
			   "used itable blocks: %d; "
			   "itable unused count: %u",
			   group, used_blks,
			   ext4_itable_unused_count(sb, gdp));
		ret = 1;
		goto err_out;
	}

	blk = ext4_inode_table(sb, gdp) + used_blks;
	num = sbi->s_itb_per_group - used_blks;

	BUFFER_TRACE(group_desc_bh, "get_write_access");
	ret = ext4_journal_get_write_access(handle,
					    group_desc_bh);
	if (ret)
		goto err_out;

	/*
	 * Skip zeroout if the inode table is full. But we set the ZEROED
	 * flag anyway, because obviously, when it is full it does not need
	 * further zeroing.
	 */
	if (unlikely(num == 0))
		goto skip_zeroout;

	ext4_debug("going to zero out inode table in group %d\n",
		   group);
	ret = sb_issue_zeroout(sb, blk, num, GFP_NOFS);
	if (ret < 0)
		goto err_out;
	if (barrier)
		blkdev_issue_flush(sb->s_bdev, GFP_NOFS, NULL);

skip_zeroout:
	ext4_lock_group(sb, group);
	gdp->bg_flags |= cpu_to_le16(EXT4_BG_INODE_ZEROED);
	ext4_group_desc_csum_set(sb, group, gdp);
	ext4_unlock_group(sb, group);

	BUFFER_TRACE(group_desc_bh,
		     "call ext4_handle_dirty_metadata");
	ret = ext4_handle_dirty_metadata(handle, NULL,
					 group_desc_bh);

err_out:
	up_write(&grp->alloc_sem);
	ext4_journal_stop(handle);
out:
	return ret;
}