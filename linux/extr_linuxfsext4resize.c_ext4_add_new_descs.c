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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct ext4_super_block {int /*<<< orphan*/  s_reserved_gdt_blocks; } ;
struct ext4_sb_info {struct buffer_head** s_group_desc; struct ext4_super_block* s_es; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int add_new_gdb (int /*<<< orphan*/ *,struct inode*,int) ; 
 int add_new_gdb_meta_bg (struct super_block*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ext4_bg_has_super (struct super_block*,int) ; 
 scalar_t__ ext4_bg_num_gdb (struct super_block*,int) ; 
 int ext4_has_feature_meta_bg (struct super_block*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int reserve_backup_gdb (int /*<<< orphan*/ *,struct inode*,int) ; 

__attribute__((used)) static int ext4_add_new_descs(handle_t *handle, struct super_block *sb,
			      ext4_group_t group, struct inode *resize_inode,
			      ext4_group_t count)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	struct buffer_head *gdb_bh;
	int i, gdb_off, gdb_num, err = 0;
	int meta_bg;

	meta_bg = ext4_has_feature_meta_bg(sb);
	for (i = 0; i < count; i++, group++) {
		int reserved_gdb = ext4_bg_has_super(sb, group) ?
			le16_to_cpu(es->s_reserved_gdt_blocks) : 0;

		gdb_off = group % EXT4_DESC_PER_BLOCK(sb);
		gdb_num = group / EXT4_DESC_PER_BLOCK(sb);

		/*
		 * We will only either add reserved group blocks to a backup group
		 * or remove reserved blocks for the first group in a new group block.
		 * Doing both would be mean more complex code, and sane people don't
		 * use non-sparse filesystems anymore.  This is already checked above.
		 */
		if (gdb_off) {
			gdb_bh = sbi->s_group_desc[gdb_num];
			BUFFER_TRACE(gdb_bh, "get_write_access");
			err = ext4_journal_get_write_access(handle, gdb_bh);

			if (!err && reserved_gdb && ext4_bg_num_gdb(sb, group))
				err = reserve_backup_gdb(handle, resize_inode, group);
		} else if (meta_bg != 0) {
			err = add_new_gdb_meta_bg(sb, handle, group);
		} else {
			err = add_new_gdb(handle, resize_inode, group);
		}
		if (err)
			break;
	}
	return err;
}