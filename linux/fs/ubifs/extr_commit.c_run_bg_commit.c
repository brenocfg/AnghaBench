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
 scalar_t__ COMMIT_BACKGROUND ; 
 scalar_t__ COMMIT_REQUIRED ; 
 scalar_t__ COMMIT_RUNNING_BACKGROUND ; 
 scalar_t__ COMMIT_RUNNING_REQUIRED ; 
 int do_commit (struct ubifs_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_bg_commit(struct ubifs_info *c)
{
	spin_lock(&c->cs_lock);
	/*
	 * Run background commit only if background commit was requested or if
	 * commit is required.
	 */
	if (c->cmt_state != COMMIT_BACKGROUND &&
	    c->cmt_state != COMMIT_REQUIRED)
		goto out;
	spin_unlock(&c->cs_lock);

	down_write(&c->commit_sem);
	spin_lock(&c->cs_lock);
	if (c->cmt_state == COMMIT_REQUIRED)
		c->cmt_state = COMMIT_RUNNING_REQUIRED;
	else if (c->cmt_state == COMMIT_BACKGROUND)
		c->cmt_state = COMMIT_RUNNING_BACKGROUND;
	else
		goto out_cmt_unlock;
	spin_unlock(&c->cs_lock);

	return do_commit(c);

out_cmt_unlock:
	up_write(&c->commit_sem);
out:
	spin_unlock(&c->cs_lock);
	return 0;
}