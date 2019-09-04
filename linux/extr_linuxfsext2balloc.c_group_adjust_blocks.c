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
struct ext2_sb_info {int dummy; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_free_blocks_count; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  sb_bgl_lock (struct ext2_sb_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void group_adjust_blocks(struct super_block *sb, int group_no,
	struct ext2_group_desc *desc, struct buffer_head *bh, int count)
{
	if (count) {
		struct ext2_sb_info *sbi = EXT2_SB(sb);
		unsigned free_blocks;

		spin_lock(sb_bgl_lock(sbi, group_no));
		free_blocks = le16_to_cpu(desc->bg_free_blocks_count);
		desc->bg_free_blocks_count = cpu_to_le16(free_blocks + count);
		spin_unlock(sb_bgl_lock(sbi, group_no));
		mark_buffer_dirty(bh);
	}
}