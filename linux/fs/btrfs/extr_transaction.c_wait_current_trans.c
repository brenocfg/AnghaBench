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
struct btrfs_transaction {scalar_t__ state; scalar_t__ aborted; int /*<<< orphan*/  use_count; } ;
struct btrfs_fs_info {int /*<<< orphan*/  trans_lock; int /*<<< orphan*/  transaction_wait; struct btrfs_transaction* running_transaction; } ;

/* Variables and functions */
 scalar_t__ TRANS_STATE_UNBLOCKED ; 
 int /*<<< orphan*/  btrfs_put_transaction (struct btrfs_transaction*) ; 
 scalar_t__ is_transaction_blocked (struct btrfs_transaction*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wait_current_trans(struct btrfs_fs_info *fs_info)
{
	struct btrfs_transaction *cur_trans;

	spin_lock(&fs_info->trans_lock);
	cur_trans = fs_info->running_transaction;
	if (cur_trans && is_transaction_blocked(cur_trans)) {
		refcount_inc(&cur_trans->use_count);
		spin_unlock(&fs_info->trans_lock);

		wait_event(fs_info->transaction_wait,
			   cur_trans->state >= TRANS_STATE_UNBLOCKED ||
			   cur_trans->aborted);
		btrfs_put_transaction(cur_trans);
	} else {
		spin_unlock(&fs_info->trans_lock);
	}
}