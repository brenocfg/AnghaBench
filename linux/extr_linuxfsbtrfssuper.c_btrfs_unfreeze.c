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
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_FROZEN ; 
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_unfreeze(struct super_block *sb)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);

	clear_bit(BTRFS_FS_FROZEN, &fs_info->flags);
	return 0;
}