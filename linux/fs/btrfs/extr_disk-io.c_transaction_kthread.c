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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ time64_t ;
struct btrfs_transaction {scalar_t__ state; scalar_t__ start_time; scalar_t__ transid; } ;
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int commit_interval; int /*<<< orphan*/  fs_state; int /*<<< orphan*/  transaction_kthread_mutex; int /*<<< orphan*/  cleaner_kthread; int /*<<< orphan*/  trans_lock; int /*<<< orphan*/  flags; struct btrfs_transaction* running_transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_NEED_ASYNC_COMMIT ; 
 int /*<<< orphan*/  BTRFS_FS_STATE_ERROR ; 
 int /*<<< orphan*/  ENOENT ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  PTR_ERR (struct btrfs_trans_handle*) ; 
 scalar_t__ TRANS_STATE_BLOCKED ; 
 struct btrfs_trans_handle* btrfs_attach_transaction (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_cleanup_transaction (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_transaction_blocked (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 scalar_t__ ktime_get_seconds () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transaction_kthread(void *arg)
{
	struct btrfs_root *root = arg;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_trans_handle *trans;
	struct btrfs_transaction *cur;
	u64 transid;
	time64_t now;
	unsigned long delay;
	bool cannot_commit;

	do {
		cannot_commit = false;
		delay = HZ * fs_info->commit_interval;
		mutex_lock(&fs_info->transaction_kthread_mutex);

		spin_lock(&fs_info->trans_lock);
		cur = fs_info->running_transaction;
		if (!cur) {
			spin_unlock(&fs_info->trans_lock);
			goto sleep;
		}

		now = ktime_get_seconds();
		if (cur->state < TRANS_STATE_BLOCKED &&
		    !test_bit(BTRFS_FS_NEED_ASYNC_COMMIT, &fs_info->flags) &&
		    (now < cur->start_time ||
		     now - cur->start_time < fs_info->commit_interval)) {
			spin_unlock(&fs_info->trans_lock);
			delay = HZ * 5;
			goto sleep;
		}
		transid = cur->transid;
		spin_unlock(&fs_info->trans_lock);

		/* If the file system is aborted, this will always fail. */
		trans = btrfs_attach_transaction(root);
		if (IS_ERR(trans)) {
			if (PTR_ERR(trans) != -ENOENT)
				cannot_commit = true;
			goto sleep;
		}
		if (transid == trans->transid) {
			btrfs_commit_transaction(trans);
		} else {
			btrfs_end_transaction(trans);
		}
sleep:
		wake_up_process(fs_info->cleaner_kthread);
		mutex_unlock(&fs_info->transaction_kthread_mutex);

		if (unlikely(test_bit(BTRFS_FS_STATE_ERROR,
				      &fs_info->fs_state)))
			btrfs_cleanup_transaction(fs_info);
		if (!kthread_should_stop() &&
				(!btrfs_transaction_blocked(fs_info) ||
				 cannot_commit))
			schedule_timeout_interruptible(delay);
	} while (!kthread_should_stop());
	return 0;
}