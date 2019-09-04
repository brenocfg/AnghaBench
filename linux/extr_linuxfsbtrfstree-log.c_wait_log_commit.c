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
struct btrfs_root {int log_transid_committed; int /*<<< orphan*/ * log_commit_wait; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/ * log_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void wait_log_commit(struct btrfs_root *root, int transid)
{
	DEFINE_WAIT(wait);
	int index = transid % 2;

	/*
	 * we only allow two pending log transactions at a time,
	 * so we know that if ours is more than 2 older than the
	 * current transaction, we're done
	 */
	for (;;) {
		prepare_to_wait(&root->log_commit_wait[index],
				&wait, TASK_UNINTERRUPTIBLE);

		if (!(root->log_transid_committed < transid &&
		      atomic_read(&root->log_commit[index])))
			break;

		mutex_unlock(&root->log_mutex);
		schedule();
		mutex_lock(&root->log_mutex);
	}
	finish_wait(&root->log_commit_wait[index], &wait);
}