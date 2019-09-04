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
struct ubifs_info {int /*<<< orphan*/  commit_sem; int /*<<< orphan*/  bi; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOSPC ; 
 int dbg_check_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_jnl (char*,...) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int reserve_space (struct ubifs_info*,int,int) ; 
 int /*<<< orphan*/  ubifs_dump_budg (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_dump_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,...) ; 
 int ubifs_run_commit (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_warn (struct ubifs_info*,char*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int make_reservation(struct ubifs_info *c, int jhead, int len)
{
	int err, cmt_retries = 0, nospc_retries = 0;

again:
	down_read(&c->commit_sem);
	err = reserve_space(c, jhead, len);
	if (!err)
		/* c->commit_sem will get released via finish_reservation(). */
		return 0;
	up_read(&c->commit_sem);

	if (err == -ENOSPC) {
		/*
		 * GC could not make any progress. We should try to commit
		 * once because it could make some dirty space and GC would
		 * make progress, so make the error -EAGAIN so that the below
		 * will commit and re-try.
		 */
		if (nospc_retries++ < 2) {
			dbg_jnl("no space, retry");
			err = -EAGAIN;
		}

		/*
		 * This means that the budgeting is incorrect. We always have
		 * to be able to write to the media, because all operations are
		 * budgeted. Deletions are not budgeted, though, but we reserve
		 * an extra LEB for them.
		 */
	}

	if (err != -EAGAIN)
		goto out;

	/*
	 * -EAGAIN means that the journal is full or too large, or the above
	 * code wants to do one commit. Do this and re-try.
	 */
	if (cmt_retries > 128) {
		/*
		 * This should not happen unless the journal size limitations
		 * are too tough.
		 */
		ubifs_err(c, "stuck in space allocation");
		err = -ENOSPC;
		goto out;
	} else if (cmt_retries > 32)
		ubifs_warn(c, "too many space allocation re-tries (%d)",
			   cmt_retries);

	dbg_jnl("-EAGAIN, commit and retry (retried %d times)",
		cmt_retries);
	cmt_retries += 1;

	err = ubifs_run_commit(c);
	if (err)
		return err;
	goto again;

out:
	ubifs_err(c, "cannot reserve %d bytes in jhead %d, error %d",
		  len, jhead, err);
	if (err == -ENOSPC) {
		/* This are some budgeting problems, print useful information */
		down_write(&c->commit_sem);
		dump_stack();
		ubifs_dump_budg(c, &c->bi);
		ubifs_dump_lprops(c);
		cmt_retries = dbg_check_lprops(c);
		up_write(&c->commit_sem);
	}
	return err;
}