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
struct btrfs_fs_info {int /*<<< orphan*/  delayed_workers; struct btrfs_delayed_root* delayed_root; } ;
struct btrfs_delayed_root {int /*<<< orphan*/  wait; int /*<<< orphan*/  items_seq; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int BTRFS_DELAYED_BACKGROUND ; 
 int /*<<< orphan*/  BTRFS_DELAYED_BATCH ; 
 int BTRFS_DELAYED_WRITEBACK ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_workqueue_normal_congested (int /*<<< orphan*/ ) ; 
 int btrfs_wq_run_delayed_node (struct btrfs_delayed_root*,struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  could_end_wait (struct btrfs_delayed_root*,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btrfs_balance_delayed_items(struct btrfs_fs_info *fs_info)
{
	struct btrfs_delayed_root *delayed_root = fs_info->delayed_root;

	if ((atomic_read(&delayed_root->items) < BTRFS_DELAYED_BACKGROUND) ||
		btrfs_workqueue_normal_congested(fs_info->delayed_workers))
		return;

	if (atomic_read(&delayed_root->items) >= BTRFS_DELAYED_WRITEBACK) {
		int seq;
		int ret;

		seq = atomic_read(&delayed_root->items_seq);

		ret = btrfs_wq_run_delayed_node(delayed_root, fs_info, 0);
		if (ret)
			return;

		wait_event_interruptible(delayed_root->wait,
					 could_end_wait(delayed_root, seq));
		return;
	}

	btrfs_wq_run_delayed_node(delayed_root, fs_info, BTRFS_DELAYED_BATCH);
}