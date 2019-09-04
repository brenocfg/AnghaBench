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
struct super_block {int /*<<< orphan*/  s_remove_count; } ;
struct ext2_sb_info {TYPE_1__* s_es; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_mount_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_state; } ;

/* Variables and functions */
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_sync_fs (struct super_block*,int) ; 
 int /*<<< orphan*/  ext2_sync_super (struct super_block*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext2_freeze(struct super_block *sb)
{
	struct ext2_sb_info *sbi = EXT2_SB(sb);

	/*
	 * Open but unlinked files present? Keep EXT2_VALID_FS flag cleared
	 * because we have unattached inodes and thus filesystem is not fully
	 * consistent.
	 */
	if (atomic_long_read(&sb->s_remove_count)) {
		ext2_sync_fs(sb, 1);
		return 0;
	}
	/* Set EXT2_FS_VALID flag */
	spin_lock(&sbi->s_lock);
	sbi->s_es->s_state = cpu_to_le16(sbi->s_mount_state);
	spin_unlock(&sbi->s_lock);
	ext2_sync_super(sb, sbi->s_es, 1);

	return 0;
}