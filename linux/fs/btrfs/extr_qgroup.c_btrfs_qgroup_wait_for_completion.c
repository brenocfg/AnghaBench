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
struct btrfs_fs_info {int qgroup_rescan_running; int /*<<< orphan*/  qgroup_rescan_completion; int /*<<< orphan*/  qgroup_rescan_lock; int /*<<< orphan*/  qgroup_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

int btrfs_qgroup_wait_for_completion(struct btrfs_fs_info *fs_info,
				     bool interruptible)
{
	int running;
	int ret = 0;

	mutex_lock(&fs_info->qgroup_rescan_lock);
	spin_lock(&fs_info->qgroup_lock);
	running = fs_info->qgroup_rescan_running;
	spin_unlock(&fs_info->qgroup_lock);
	mutex_unlock(&fs_info->qgroup_rescan_lock);

	if (!running)
		return 0;

	if (interruptible)
		ret = wait_for_completion_interruptible(
					&fs_info->qgroup_rescan_completion);
	else
		wait_for_completion(&fs_info->qgroup_rescan_completion);

	return ret;
}