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
struct super_block {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_id; } ;
struct jfs_sb_info {int flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_DIRTY ; 
 int JFS_ERR_PANIC ; 
 int JFS_ERR_REMOUNT_RO ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  jfs_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  updateSuper (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jfs_handle_error(struct super_block *sb)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);

	if (sb_rdonly(sb))
		return;

	updateSuper(sb, FM_DIRTY);

	if (sbi->flag & JFS_ERR_PANIC)
		panic("JFS (device %s): panic forced after error\n",
			sb->s_id);
	else if (sbi->flag & JFS_ERR_REMOUNT_RO) {
		jfs_err("ERROR: (device %s): remounting filesystem as read-only",
			sb->s_id);
		sb->s_flags |= SB_RDONLY;
	}

	/* nothing is done for continue beyond marking the superblock dirty */
}