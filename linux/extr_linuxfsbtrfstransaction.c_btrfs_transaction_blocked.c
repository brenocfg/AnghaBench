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
struct btrfs_transaction {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  trans_lock; struct btrfs_transaction* running_transaction; } ;

/* Variables and functions */
 int is_transaction_blocked (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_transaction_blocked(struct btrfs_fs_info *info)
{
	struct btrfs_transaction *trans;
	int ret = 0;

	spin_lock(&info->trans_lock);
	trans = info->running_transaction;
	if (trans)
		ret = is_transaction_blocked(trans);
	spin_unlock(&info->trans_lock);
	return ret;
}