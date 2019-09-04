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
struct super_block {scalar_t__ s_bdev; scalar_t__ s_mtd; } ;
struct cramfs_sb_info {int /*<<< orphan*/  mtd_point_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRAMFS_BLOCKDEV ; 
 int /*<<< orphan*/  CONFIG_CRAMFS_MTD ; 
 struct cramfs_sb_info* CRAMFS_SB (struct super_block*) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cramfs_sb_info*) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 
 int /*<<< orphan*/  kill_mtd_super (struct super_block*) ; 
 int /*<<< orphan*/  mtd_unpoint (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cramfs_kill_sb(struct super_block *sb)
{
	struct cramfs_sb_info *sbi = CRAMFS_SB(sb);

	if (IS_ENABLED(CONFIG_CRAMFS_MTD) && sb->s_mtd) {
		if (sbi && sbi->mtd_point_size)
			mtd_unpoint(sb->s_mtd, 0, sbi->mtd_point_size);
		kill_mtd_super(sb);
	} else if (IS_ENABLED(CONFIG_CRAMFS_BLOCKDEV) && sb->s_bdev) {
		kill_block_super(sb);
	}
	kfree(sbi);
}