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
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_CLOSING_DONE ; 
 int /*<<< orphan*/  BTRFS_FS_CLOSING_START ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int btrfs_fs_closing(struct btrfs_fs_info *fs_info)
{
	/*
	 * Do it this way so we only ever do one test_bit in the normal case.
	 */
	if (test_bit(BTRFS_FS_CLOSING_START, &fs_info->flags)) {
		if (test_bit(BTRFS_FS_CLOSING_DONE, &fs_info->flags))
			return 2;
		return 1;
	}
	return 0;
}