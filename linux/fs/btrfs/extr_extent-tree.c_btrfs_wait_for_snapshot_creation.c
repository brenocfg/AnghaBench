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
struct btrfs_root {int /*<<< orphan*/  will_be_snapshotted; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int btrfs_start_write_no_snapshotting (struct btrfs_root*) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 

void btrfs_wait_for_snapshot_creation(struct btrfs_root *root)
{
	while (true) {
		int ret;

		ret = btrfs_start_write_no_snapshotting(root);
		if (ret)
			break;
		wait_var_event(&root->will_be_snapshotted,
			       !atomic_read(&root->will_be_snapshotted));
	}
}