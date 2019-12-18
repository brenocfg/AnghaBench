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
struct super_block {int dummy; } ;
struct list_head {int dummy; } ;
struct ext4_sb_info {TYPE_1__* s_es; } ;
typedef  unsigned long ext4_group_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_reserved_gdt_blocks; int /*<<< orphan*/  s_first_meta_bg; } ;

/* Variables and functions */
 unsigned long EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_FS ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_GDT ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_RESV_GDT ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_bg_has_super (struct super_block*,unsigned long) ; 
 int ext4_bg_num_gdb (struct super_block*,unsigned long) ; 
 int ext4_getfsmap_fill (struct list_head*,int,int,int /*<<< orphan*/ ) ; 
 int ext4_group_first_block_no (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  ext4_has_feature_meta_bg (struct super_block*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ext4_getfsmap_find_sb(struct super_block *sb,
					  ext4_group_t agno,
					  struct list_head *meta_list)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t fsb = ext4_group_first_block_no(sb, agno);
	ext4_fsblk_t len;
	unsigned long first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);
	unsigned long metagroup = agno / EXT4_DESC_PER_BLOCK(sb);
	int error;

	/* Record the superblock. */
	if (ext4_bg_has_super(sb, agno)) {
		error = ext4_getfsmap_fill(meta_list, fsb, 1, EXT4_FMR_OWN_FS);
		if (error)
			return error;
		fsb++;
	}

	/* Record the group descriptors. */
	len = ext4_bg_num_gdb(sb, agno);
	if (!len)
		return 0;
	error = ext4_getfsmap_fill(meta_list, fsb, len,
				   EXT4_FMR_OWN_GDT);
	if (error)
		return error;
	fsb += len;

	/* Reserved GDT blocks */
	if (!ext4_has_feature_meta_bg(sb) || metagroup < first_meta_bg) {
		len = le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks);
		error = ext4_getfsmap_fill(meta_list, fsb, len,
					   EXT4_FMR_OWN_RESV_GDT);
		if (error)
			return error;
	}

	return 0;
}