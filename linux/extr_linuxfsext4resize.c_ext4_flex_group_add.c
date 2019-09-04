#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct ext4_super_block {int /*<<< orphan*/  s_reserved_gdt_blocks; } ;
struct ext4_sb_info {int s_groups_count; struct buffer_head** s_group_desc; TYPE_2__* s_sbh; struct ext4_super_block* s_es; } ;
struct ext4_new_flex_group_data {int count; TYPE_1__* groups; int /*<<< orphan*/  bg_flags; } ;
struct buffer_head {scalar_t__ b_blocknr; char* b_data; int b_size; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_grpblk_t ;
typedef  int ext4_group_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
struct TYPE_5__ {scalar_t__ b_blocknr; } ;
struct TYPE_4__ {int group; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_HT_RESIZE ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ext4_add_new_descs (int /*<<< orphan*/ *,struct super_block*,int,struct inode*,int) ; 
 int /*<<< orphan*/  ext4_blocks_count (struct ext4_super_block*) ; 
 int /*<<< orphan*/  ext4_get_group_no_and_offset (struct super_block*,int /*<<< orphan*/ ,int*,int*) ; 
 int ext4_handle_dirty_super (int /*<<< orphan*/ *,struct super_block*) ; 
 int ext4_has_feature_meta_bg (struct super_block*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * ext4_journal_start_sb (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_setup_new_descs (int /*<<< orphan*/ *,struct super_block*,struct ext4_new_flex_group_data*) ; 
 int /*<<< orphan*/  ext4_update_super (struct super_block*,struct ext4_new_flex_group_data*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int setup_new_flex_group_blocks (struct super_block*,struct ext4_new_flex_group_data*) ; 
 int /*<<< orphan*/  update_backups (struct super_block*,scalar_t__,char*,int,int) ; 

__attribute__((used)) static int ext4_flex_group_add(struct super_block *sb,
			       struct inode *resize_inode,
			       struct ext4_new_flex_group_data *flex_gd)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	ext4_fsblk_t o_blocks_count;
	ext4_grpblk_t last;
	ext4_group_t group;
	handle_t *handle;
	unsigned reserved_gdb;
	int err = 0, err2 = 0, credit;

	BUG_ON(!flex_gd->count || !flex_gd->groups || !flex_gd->bg_flags);

	reserved_gdb = le16_to_cpu(es->s_reserved_gdt_blocks);
	o_blocks_count = ext4_blocks_count(es);
	ext4_get_group_no_and_offset(sb, o_blocks_count, &group, &last);
	BUG_ON(last);

	err = setup_new_flex_group_blocks(sb, flex_gd);
	if (err)
		goto exit;
	/*
	 * We will always be modifying at least the superblock and  GDT
	 * blocks.  If we are adding a group past the last current GDT block,
	 * we will also modify the inode and the dindirect block.  If we
	 * are adding a group with superblock/GDT backups  we will also
	 * modify each of the reserved GDT dindirect blocks.
	 */
	credit = 3;	/* sb, resize inode, resize inode dindirect */
	/* GDT blocks */
	credit += 1 + DIV_ROUND_UP(flex_gd->count, EXT4_DESC_PER_BLOCK(sb));
	credit += reserved_gdb;	/* Reserved GDT dindirect blocks */
	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, credit);
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		goto exit;
	}

	BUFFER_TRACE(sbi->s_sbh, "get_write_access");
	err = ext4_journal_get_write_access(handle, sbi->s_sbh);
	if (err)
		goto exit_journal;

	group = flex_gd->groups[0].group;
	BUG_ON(group != sbi->s_groups_count);
	err = ext4_add_new_descs(handle, sb, group,
				resize_inode, flex_gd->count);
	if (err)
		goto exit_journal;

	err = ext4_setup_new_descs(handle, sb, flex_gd);
	if (err)
		goto exit_journal;

	ext4_update_super(sb, flex_gd);

	err = ext4_handle_dirty_super(handle, sb);

exit_journal:
	err2 = ext4_journal_stop(handle);
	if (!err)
		err = err2;

	if (!err) {
		int gdb_num = group / EXT4_DESC_PER_BLOCK(sb);
		int gdb_num_end = ((group + flex_gd->count - 1) /
				   EXT4_DESC_PER_BLOCK(sb));
		int meta_bg = ext4_has_feature_meta_bg(sb);
		sector_t old_gdb = 0;

		update_backups(sb, sbi->s_sbh->b_blocknr, (char *)es,
			       sizeof(struct ext4_super_block), 0);
		for (; gdb_num <= gdb_num_end; gdb_num++) {
			struct buffer_head *gdb_bh;

			gdb_bh = sbi->s_group_desc[gdb_num];
			if (old_gdb == gdb_bh->b_blocknr)
				continue;
			update_backups(sb, gdb_bh->b_blocknr, gdb_bh->b_data,
				       gdb_bh->b_size, meta_bg);
			old_gdb = gdb_bh->b_blocknr;
		}
	}
exit:
	return err;
}