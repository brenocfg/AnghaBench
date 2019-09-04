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
struct inode {scalar_t__ i_blocks; } ;
struct f2fs_sb_info {scalar_t__ total_valid_block_count; scalar_t__ reserved_blocks; scalar_t__ current_reserved_blocks; int /*<<< orphan*/  stat_lock; } ;
typedef  scalar_t__ block_t ;
typedef  scalar_t__ blkcnt_t ;

/* Variables and functions */
 scalar_t__ F2FS_LOG_SECTORS_PER_BLOCK ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_i_blocks_write (struct inode*,scalar_t__,int,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dec_valid_block_count(struct f2fs_sb_info *sbi,
						struct inode *inode,
						block_t count)
{
	blkcnt_t sectors = count << F2FS_LOG_SECTORS_PER_BLOCK;

	spin_lock(&sbi->stat_lock);
	f2fs_bug_on(sbi, sbi->total_valid_block_count < (block_t) count);
	f2fs_bug_on(sbi, inode->i_blocks < sectors);
	sbi->total_valid_block_count -= (block_t)count;
	if (sbi->reserved_blocks &&
		sbi->current_reserved_blocks < sbi->reserved_blocks)
		sbi->current_reserved_blocks = min(sbi->reserved_blocks,
					sbi->current_reserved_blocks + count);
	spin_unlock(&sbi->stat_lock);
	f2fs_i_blocks_write(inode, count, false, true);
}