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
struct btrfs_root {int /*<<< orphan*/  log_writer_wait; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  log_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void wait_for_writer(struct btrfs_root *root)
{
	DEFINE_WAIT(wait);

	for (;;) {
		prepare_to_wait(&root->log_writer_wait, &wait,
				TASK_UNINTERRUPTIBLE);
		if (!atomic_read(&root->log_writers))
			break;

		mutex_unlock(&root->log_mutex);
		schedule();
		mutex_lock(&root->log_mutex);
	}
	finish_wait(&root->log_writer_wait, &wait);
}