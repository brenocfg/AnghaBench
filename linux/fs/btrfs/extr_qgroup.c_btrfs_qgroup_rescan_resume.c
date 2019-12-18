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
struct btrfs_fs_info {int qgroup_flags; int /*<<< orphan*/  qgroup_rescan_work; int /*<<< orphan*/  qgroup_rescan_workers; } ;

/* Variables and functions */
 int BTRFS_QGROUP_STATUS_FLAG_RESCAN ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
btrfs_qgroup_rescan_resume(struct btrfs_fs_info *fs_info)
{
	if (fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_RESCAN)
		btrfs_queue_work(fs_info->qgroup_rescan_workers,
				 &fs_info->qgroup_rescan_work);
}