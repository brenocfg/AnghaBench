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
struct inode {struct super_block* i_sb; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_dirtyclusters_counter; int /*<<< orphan*/  s_freeclusters_counter; } ;
struct ext4_inode_info {long long i_reserved_data_blocks; } ;

/* Variables and functions */
 long long EXT4_C2B (struct ext4_sb_info*,int /*<<< orphan*/ ) ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  ext4_count_free_clusters (struct super_block*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  percpu_counter_sum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_print_free_blocks(struct inode *inode)
{
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct super_block *sb = inode->i_sb;
	struct ext4_inode_info *ei = EXT4_I(inode);

	ext4_msg(sb, KERN_CRIT, "Total free blocks count %lld",
	       EXT4_C2B(EXT4_SB(inode->i_sb),
			ext4_count_free_clusters(sb)));
	ext4_msg(sb, KERN_CRIT, "Free/Dirty block details");
	ext4_msg(sb, KERN_CRIT, "free_blocks=%lld",
	       (long long) EXT4_C2B(EXT4_SB(sb),
		percpu_counter_sum(&sbi->s_freeclusters_counter)));
	ext4_msg(sb, KERN_CRIT, "dirty_blocks=%lld",
	       (long long) EXT4_C2B(EXT4_SB(sb),
		percpu_counter_sum(&sbi->s_dirtyclusters_counter)));
	ext4_msg(sb, KERN_CRIT, "Block reservation details");
	ext4_msg(sb, KERN_CRIT, "i_reserved_data_blocks=%u",
		 ei->i_reserved_data_blocks);
	return;
}