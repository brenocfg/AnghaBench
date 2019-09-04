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
struct btrfs_fs_info {int /*<<< orphan*/  mount_opt; int /*<<< orphan*/  pending_changes; } ;

/* Variables and functions */
 int BTRFS_PENDING_CLEAR_INODE_MAP_CACHE ; 
 int BTRFS_PENDING_COMMIT ; 
 int BTRFS_PENDING_SET_INODE_MAP_CACHE ; 
 int /*<<< orphan*/  INODE_MAP_CACHE ; 
 int /*<<< orphan*/  btrfs_clear_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_debug (struct btrfs_fs_info*,char*) ; 
 int /*<<< orphan*/  btrfs_set_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,unsigned long) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void btrfs_apply_pending_changes(struct btrfs_fs_info *fs_info)
{
	unsigned long prev;
	unsigned long bit;

	prev = xchg(&fs_info->pending_changes, 0);
	if (!prev)
		return;

	bit = 1 << BTRFS_PENDING_SET_INODE_MAP_CACHE;
	if (prev & bit)
		btrfs_set_opt(fs_info->mount_opt, INODE_MAP_CACHE);
	prev &= ~bit;

	bit = 1 << BTRFS_PENDING_CLEAR_INODE_MAP_CACHE;
	if (prev & bit)
		btrfs_clear_opt(fs_info->mount_opt, INODE_MAP_CACHE);
	prev &= ~bit;

	bit = 1 << BTRFS_PENDING_COMMIT;
	if (prev & bit)
		btrfs_debug(fs_info, "pending commit done");
	prev &= ~bit;

	if (prev)
		btrfs_warn(fs_info,
			"unknown pending changes left 0x%lx, ignoring", prev);
}