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
struct ext4_super_block {int /*<<< orphan*/  s_reserved_gdt_blocks; int /*<<< orphan*/  s_inodes_count; } ;
struct ext4_sb_info {struct ext4_super_block* s_es; } ;
struct ext4_new_group_data {int group; scalar_t__ blocks_count; } ;
struct ext4_new_flex_group_data {int count; int /*<<< orphan*/ * bg_flags; struct ext4_new_group_data* groups; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_IGET_SPECIAL ; 
 scalar_t__ EXT4_INODES_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_RESIZE_INO ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int ext4_alloc_flex_bg_array (struct super_block*,int) ; 
 scalar_t__ ext4_bg_has_super (struct super_block*,int) ; 
 scalar_t__ ext4_blocks_count (struct ext4_super_block*) ; 
 int ext4_flex_group_add (struct super_block*,struct inode*,struct ext4_new_flex_group_data*) ; 
 int /*<<< orphan*/  ext4_has_feature_resize_inode (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_feature_sparse_super (struct super_block*) ; 
 struct inode* ext4_iget (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_mb_alloc_groupinfo (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int verify_group_input (struct super_block*,struct ext4_new_group_data*) ; 

int ext4_group_add(struct super_block *sb, struct ext4_new_group_data *input)
{
	struct ext4_new_flex_group_data flex_gd;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_super_block *es = sbi->s_es;
	int reserved_gdb = ext4_bg_has_super(sb, input->group) ?
		le16_to_cpu(es->s_reserved_gdt_blocks) : 0;
	struct inode *inode = NULL;
	int gdb_off;
	int err;
	__u16 bg_flags = 0;

	gdb_off = input->group % EXT4_DESC_PER_BLOCK(sb);

	if (gdb_off == 0 && !ext4_has_feature_sparse_super(sb)) {
		ext4_warning(sb, "Can't resize non-sparse filesystem further");
		return -EPERM;
	}

	if (ext4_blocks_count(es) + input->blocks_count <
	    ext4_blocks_count(es)) {
		ext4_warning(sb, "blocks_count overflow");
		return -EINVAL;
	}

	if (le32_to_cpu(es->s_inodes_count) + EXT4_INODES_PER_GROUP(sb) <
	    le32_to_cpu(es->s_inodes_count)) {
		ext4_warning(sb, "inodes_count overflow");
		return -EINVAL;
	}

	if (reserved_gdb || gdb_off == 0) {
		if (!ext4_has_feature_resize_inode(sb) ||
		    !le16_to_cpu(es->s_reserved_gdt_blocks)) {
			ext4_warning(sb,
				     "No reserved GDT blocks, can't resize");
			return -EPERM;
		}
		inode = ext4_iget(sb, EXT4_RESIZE_INO, EXT4_IGET_SPECIAL);
		if (IS_ERR(inode)) {
			ext4_warning(sb, "Error opening resize inode");
			return PTR_ERR(inode);
		}
	}


	err = verify_group_input(sb, input);
	if (err)
		goto out;

	err = ext4_alloc_flex_bg_array(sb, input->group + 1);
	if (err)
		goto out;

	err = ext4_mb_alloc_groupinfo(sb, input->group + 1);
	if (err)
		goto out;

	flex_gd.count = 1;
	flex_gd.groups = input;
	flex_gd.bg_flags = &bg_flags;
	err = ext4_flex_group_add(sb, inode, &flex_gd);
out:
	iput(inode);
	return err;
}