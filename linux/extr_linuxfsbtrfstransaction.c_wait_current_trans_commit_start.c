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
struct btrfs_transaction {scalar_t__ state; scalar_t__ aborted; } ;
struct btrfs_fs_info {int /*<<< orphan*/  transaction_blocked_wait; } ;

/* Variables and functions */
 scalar_t__ TRANS_STATE_COMMIT_START ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wait_current_trans_commit_start(struct btrfs_fs_info *fs_info,
					    struct btrfs_transaction *trans)
{
	wait_event(fs_info->transaction_blocked_wait,
		   trans->state >= TRANS_STATE_COMMIT_START || trans->aborted);
}