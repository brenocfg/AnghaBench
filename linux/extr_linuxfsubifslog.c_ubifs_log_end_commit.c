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
struct ubifs_info {int ltail_lnum; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  buds_lock; scalar_t__ cmt_bud_bytes; int /*<<< orphan*/  bud_bytes; int /*<<< orphan*/  leb_size; int /*<<< orphan*/  min_log_bytes; } ;

/* Variables and functions */
 int dbg_check_bud_bytes (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_log (char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubifs_write_master (struct ubifs_info*) ; 

int ubifs_log_end_commit(struct ubifs_info *c, int ltail_lnum)
{
	int err;

	/*
	 * At this phase we have to lock 'c->log_mutex' because UBIFS allows FS
	 * writes during commit. Its only short "commit" start phase when
	 * writers are blocked.
	 */
	mutex_lock(&c->log_mutex);

	dbg_log("old tail was LEB %d:0, new tail is LEB %d:0",
		c->ltail_lnum, ltail_lnum);

	c->ltail_lnum = ltail_lnum;
	/*
	 * The commit is finished and from now on it must be guaranteed that
	 * there is always enough space for the next commit.
	 */
	c->min_log_bytes = c->leb_size;

	spin_lock(&c->buds_lock);
	c->bud_bytes -= c->cmt_bud_bytes;
	spin_unlock(&c->buds_lock);

	err = dbg_check_bud_bytes(c);
	if (err)
		goto out;

	err = ubifs_write_master(c);

out:
	mutex_unlock(&c->log_mutex);
	return err;
}