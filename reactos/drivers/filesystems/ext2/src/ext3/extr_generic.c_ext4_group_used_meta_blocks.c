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
struct ext4_group_desc {int dummy; } ;
struct ext3_sb_info {int s_itb_per_group; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 scalar_t__ EXT3_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_FLEX_BG ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_block_in_group (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  fini_bh (struct buffer_head**) ; 

__attribute__((used)) static int ext4_group_used_meta_blocks(struct super_block *sb,
                                       ext4_group_t block_group)
{
    ext4_fsblk_t tmp;
    struct ext3_sb_info *sbi = EXT3_SB(sb);
    /* block bitmap, inode bitmap, and inode table blocks */
    int used_blocks = sbi->s_itb_per_group + 2;

    if (EXT3_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_FLEX_BG)) {
        struct ext4_group_desc *gdp;
        struct buffer_head *bh = NULL;

        gdp = ext4_get_group_desc(sb, block_group, &bh);
        if (!ext4_block_in_group(sb, ext4_block_bitmap(sb, gdp),
                                 block_group))
            used_blocks--;

        if (!ext4_block_in_group(sb, ext4_inode_bitmap(sb, gdp),
                                 block_group))
            used_blocks--;

        tmp = ext4_inode_table(sb, gdp);
        for (; tmp < ext4_inode_table(sb, gdp) +
                sbi->s_itb_per_group; tmp++) {
            if (!ext4_block_in_group(sb, tmp, block_group))
                used_blocks -= 1;
        }
        if (bh)
            fini_bh(&bh);
    }
    return used_blocks;
}