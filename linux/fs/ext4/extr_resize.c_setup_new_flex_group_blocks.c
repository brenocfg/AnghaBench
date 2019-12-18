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
struct ext4_super_block {int /*<<< orphan*/  s_reserved_gdt_blocks; } ;
struct ext4_sb_info {int s_itb_per_group; scalar_t__ s_groups_count; TYPE_1__** s_group_desc; struct ext4_super_block* s_es; } ;
struct ext4_new_group_data {scalar_t__ group; scalar_t__ inode_table; scalar_t__ block_bitmap; scalar_t__ blocks_count; scalar_t__ inode_bitmap; } ;
struct ext4_new_flex_group_data {int* bg_flags; int count; struct ext4_new_group_data* groups; } ;
struct buffer_head {int /*<<< orphan*/  b_data; int /*<<< orphan*/  b_size; } ;
typedef  struct buffer_head handle_t ;
typedef  scalar_t__ ext4_grpblk_t ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
typedef  int __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 int EXT4_BG_BLOCK_UNINIT ; 
 int EXT4_BG_INODE_UNINIT ; 
 int EXT4_BG_INODE_ZEROED ; 
 int /*<<< orphan*/  EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_HT_RESIZE ; 
 int /*<<< orphan*/  EXT4_INODES_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_MAX_TRANS_DATA ; 
 int /*<<< orphan*/  EXT4_NUM_B2C (struct ext4_sb_info*,scalar_t__) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int GROUP_TABLE_COUNT ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 struct buffer_head* bclean (struct buffer_head*,struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ ext4_bg_has_super (struct super_block*,scalar_t__) ; 
 unsigned long ext4_bg_num_gdb (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_debug (char*,scalar_t__,...) ; 
 scalar_t__ ext4_group_first_block_no (struct super_block*,scalar_t__) ; 
 scalar_t__ ext4_group_overhead_blocks (struct super_block*,scalar_t__) ; 
 int ext4_handle_dirty_metadata (struct buffer_head*,int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext4_has_feature_meta_bg (struct super_block*) ; 
 int ext4_journal_get_write_access (struct buffer_head*,struct buffer_head*) ; 
 struct buffer_head* ext4_journal_start_sb (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_journal_stop (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_bitmap_end (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_meta_bg_first_group (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int extend_or_restart_transaction (struct buffer_head*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (struct super_block*,scalar_t__) ; 
 int sb_issue_zeroout (struct super_block*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int set_flexbg_block_bitmap (struct super_block*,struct buffer_head*,struct ext4_new_flex_group_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int setup_new_flex_group_blocks(struct super_block *sb,
				struct ext4_new_flex_group_data *flex_gd)
{
	int group_table_count[] = {1, 1, EXT4_SB(sb)->s_itb_per_group};
	ext4_fsblk_t start;
	ext4_fsblk_t block;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	struct ext4_new_group_data *group_data = flex_gd->groups;
	__u16 *bg_flags = flex_gd->bg_flags;
	handle_t *handle;
	ext4_group_t group, count;
	struct buffer_head *bh = NULL;
	int reserved_gdb, i, j, err = 0, err2;
	int meta_bg;

	BUG_ON(!flex_gd->count || !group_data ||
	       group_data[0].group != sbi->s_groups_count);

	reserved_gdb = le16_to_cpu(es->s_reserved_gdt_blocks);
	meta_bg = ext4_has_feature_meta_bg(sb);

	/* This transaction may be extended/restarted along the way */
	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, EXT4_MAX_TRANS_DATA);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	group = group_data[0].group;
	for (i = 0; i < flex_gd->count; i++, group++) {
		unsigned long gdblocks;
		ext4_grpblk_t overhead;

		gdblocks = ext4_bg_num_gdb(sb, group);
		start = ext4_group_first_block_no(sb, group);

		if (meta_bg == 0 && !ext4_bg_has_super(sb, group))
			goto handle_itb;

		if (meta_bg == 1) {
			ext4_group_t first_group;
			first_group = ext4_meta_bg_first_group(sb, group);
			if (first_group != group + 1 &&
			    first_group != group + EXT4_DESC_PER_BLOCK(sb) - 1)
				goto handle_itb;
		}

		block = start + ext4_bg_has_super(sb, group);
		/* Copy all of the GDT blocks into the backup in this group */
		for (j = 0; j < gdblocks; j++, block++) {
			struct buffer_head *gdb;

			ext4_debug("update backup group %#04llx\n", block);
			err = extend_or_restart_transaction(handle, 1);
			if (err)
				goto out;

			gdb = sb_getblk(sb, block);
			if (unlikely(!gdb)) {
				err = -ENOMEM;
				goto out;
			}

			BUFFER_TRACE(gdb, "get_write_access");
			err = ext4_journal_get_write_access(handle, gdb);
			if (err) {
				brelse(gdb);
				goto out;
			}
			memcpy(gdb->b_data, sbi->s_group_desc[j]->b_data,
			       gdb->b_size);
			set_buffer_uptodate(gdb);

			err = ext4_handle_dirty_metadata(handle, NULL, gdb);
			if (unlikely(err)) {
				brelse(gdb);
				goto out;
			}
			brelse(gdb);
		}

		/* Zero out all of the reserved backup group descriptor
		 * table blocks
		 */
		if (ext4_bg_has_super(sb, group)) {
			err = sb_issue_zeroout(sb, gdblocks + start + 1,
					reserved_gdb, GFP_NOFS);
			if (err)
				goto out;
		}

handle_itb:
		/* Initialize group tables of the grop @group */
		if (!(bg_flags[i] & EXT4_BG_INODE_ZEROED))
			goto handle_bb;

		/* Zero out all of the inode table blocks */
		block = group_data[i].inode_table;
		ext4_debug("clear inode table blocks %#04llx -> %#04lx\n",
			   block, sbi->s_itb_per_group);
		err = sb_issue_zeroout(sb, block, sbi->s_itb_per_group,
				       GFP_NOFS);
		if (err)
			goto out;

handle_bb:
		if (bg_flags[i] & EXT4_BG_BLOCK_UNINIT)
			goto handle_ib;

		/* Initialize block bitmap of the @group */
		block = group_data[i].block_bitmap;
		err = extend_or_restart_transaction(handle, 1);
		if (err)
			goto out;

		bh = bclean(handle, sb, block);
		if (IS_ERR(bh)) {
			err = PTR_ERR(bh);
			goto out;
		}
		overhead = ext4_group_overhead_blocks(sb, group);
		if (overhead != 0) {
			ext4_debug("mark backup superblock %#04llx (+0)\n",
				   start);
			ext4_set_bits(bh->b_data, 0,
				      EXT4_NUM_B2C(sbi, overhead));
		}
		ext4_mark_bitmap_end(EXT4_B2C(sbi, group_data[i].blocks_count),
				     sb->s_blocksize * 8, bh->b_data);
		err = ext4_handle_dirty_metadata(handle, NULL, bh);
		brelse(bh);
		if (err)
			goto out;

handle_ib:
		if (bg_flags[i] & EXT4_BG_INODE_UNINIT)
			continue;

		/* Initialize inode bitmap of the @group */
		block = group_data[i].inode_bitmap;
		err = extend_or_restart_transaction(handle, 1);
		if (err)
			goto out;
		/* Mark unused entries in inode bitmap used */
		bh = bclean(handle, sb, block);
		if (IS_ERR(bh)) {
			err = PTR_ERR(bh);
			goto out;
		}

		ext4_mark_bitmap_end(EXT4_INODES_PER_GROUP(sb),
				     sb->s_blocksize * 8, bh->b_data);
		err = ext4_handle_dirty_metadata(handle, NULL, bh);
		brelse(bh);
		if (err)
			goto out;
	}

	/* Mark group tables in block bitmap */
	for (j = 0; j < GROUP_TABLE_COUNT; j++) {
		count = group_table_count[j];
		start = (&group_data[0].block_bitmap)[j];
		block = start;
		for (i = 1; i < flex_gd->count; i++) {
			block += group_table_count[j];
			if (block == (&group_data[i].block_bitmap)[j]) {
				count += group_table_count[j];
				continue;
			}
			err = set_flexbg_block_bitmap(sb, handle,
						      flex_gd,
						      EXT4_B2C(sbi, start),
						      EXT4_B2C(sbi,
							       start + count
							       - 1));
			if (err)
				goto out;
			count = group_table_count[j];
			start = (&group_data[i].block_bitmap)[j];
			block = start;
		}

		if (count) {
			err = set_flexbg_block_bitmap(sb, handle,
						      flex_gd,
						      EXT4_B2C(sbi, start),
						      EXT4_B2C(sbi,
							       start + count
							       - 1));
			if (err)
				goto out;
		}
	}

out:
	err2 = ext4_journal_stop(handle);
	if (err2 && !err)
		err = err2;

	return err;
}