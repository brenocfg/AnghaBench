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
struct btrfs_inode {int /*<<< orphan*/  sync_writers; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_CSUM_IMPL_FAST ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_async_write(struct btrfs_fs_info *fs_info,
			     struct btrfs_inode *bi)
{
	if (atomic_read(&bi->sync_writers))
		return 0;
	if (test_bit(BTRFS_FS_CSUM_IMPL_FAST, &fs_info->flags))
		return 0;
	return 1;
}