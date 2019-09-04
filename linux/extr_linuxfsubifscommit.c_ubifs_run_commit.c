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
struct ubifs_info {scalar_t__ cmt_state; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  commit_sem; } ;

/* Variables and functions */
 scalar_t__ COMMIT_BROKEN ; 
 scalar_t__ COMMIT_RUNNING_BACKGROUND ; 
 scalar_t__ COMMIT_RUNNING_REQUIRED ; 
 int EROFS ; 
 int do_commit (struct ubifs_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int wait_for_commit (struct ubifs_info*) ; 

int ubifs_run_commit(struct ubifs_info *c)
{
	int err = 0;

	spin_lock(&c->cs_lock);
	if (c->cmt_state == COMMIT_BROKEN) {
		err = -EROFS;
		goto out;
	}

	if (c->cmt_state == COMMIT_RUNNING_BACKGROUND)
		/*
		 * We set the commit state to 'running required' to indicate
		 * that we want it to complete as quickly as possible.
		 */
		c->cmt_state = COMMIT_RUNNING_REQUIRED;

	if (c->cmt_state == COMMIT_RUNNING_REQUIRED) {
		spin_unlock(&c->cs_lock);
		return wait_for_commit(c);
	}
	spin_unlock(&c->cs_lock);

	/* Ok, the commit is indeed needed */

	down_write(&c->commit_sem);
	spin_lock(&c->cs_lock);
	/*
	 * Since we unlocked 'c->cs_lock', the state may have changed, so
	 * re-check it.
	 */
	if (c->cmt_state == COMMIT_BROKEN) {
		err = -EROFS;
		goto out_cmt_unlock;
	}

	if (c->cmt_state == COMMIT_RUNNING_BACKGROUND)
		c->cmt_state = COMMIT_RUNNING_REQUIRED;

	if (c->cmt_state == COMMIT_RUNNING_REQUIRED) {
		up_write(&c->commit_sem);
		spin_unlock(&c->cs_lock);
		return wait_for_commit(c);
	}
	c->cmt_state = COMMIT_RUNNING_REQUIRED;
	spin_unlock(&c->cs_lock);

	err = do_commit(c);
	return err;

out_cmt_unlock:
	up_write(&c->commit_sem);
out:
	spin_unlock(&c->cs_lock);
	return err;
}