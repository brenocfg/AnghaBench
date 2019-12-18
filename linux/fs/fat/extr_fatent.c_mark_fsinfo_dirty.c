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
struct msdos_sb_info {int /*<<< orphan*/  fsinfo_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_SYNC ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_fat32 (struct msdos_sb_info*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

__attribute__((used)) static void mark_fsinfo_dirty(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	if (sb_rdonly(sb) || !is_fat32(sbi))
		return;

	__mark_inode_dirty(sbi->fsinfo_inode, I_DIRTY_SYNC);
}