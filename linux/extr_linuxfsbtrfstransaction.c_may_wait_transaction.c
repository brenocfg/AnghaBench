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
 int /*<<< orphan*/  BTRFS_FS_LOG_RECOVERING ; 
 int TRANS_START ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int may_wait_transaction(struct btrfs_fs_info *fs_info, int type)
{
	if (test_bit(BTRFS_FS_LOG_RECOVERING, &fs_info->flags))
		return 0;

	if (type == TRANS_START)
		return 1;

	return 0;
}