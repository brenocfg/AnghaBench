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
struct tblock {int flag; int xflag; int /*<<< orphan*/  gcwait; } ;
struct jfs_log {int cflag; int /*<<< orphan*/  gcrtc; int /*<<< orphan*/  flag; int /*<<< orphan*/  cqueue; } ;

/* Variables and functions */
 int COMMIT_LAZY ; 
 int EIO ; 
 int /*<<< orphan*/  LOGGC_LOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  LOGGC_UNLOCK (struct jfs_log*) ; 
 int /*<<< orphan*/  __SLEEP_COND (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_info (char*,struct tblock*,int /*<<< orphan*/ ) ; 
 scalar_t__ jfs_tlocks_low ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmGCwrite (struct jfs_log*,int /*<<< orphan*/ ) ; 
 int logGC_PAGEOUT ; 
 int /*<<< orphan*/  log_FLUSH ; 
 int tblkGC_COMMITTED ; 
 int tblkGC_ERROR ; 
 int tblkGC_LAZY ; 
 int tblkGC_READY ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int lmGroupCommit(struct jfs_log * log, struct tblock * tblk)
{
	int rc = 0;

	LOGGC_LOCK(log);

	/* group committed already ? */
	if (tblk->flag & tblkGC_COMMITTED) {
		if (tblk->flag & tblkGC_ERROR)
			rc = -EIO;

		LOGGC_UNLOCK(log);
		return rc;
	}
	jfs_info("lmGroup Commit: tblk = 0x%p, gcrtc = %d", tblk, log->gcrtc);

	if (tblk->xflag & COMMIT_LAZY)
		tblk->flag |= tblkGC_LAZY;

	if ((!(log->cflag & logGC_PAGEOUT)) && (!list_empty(&log->cqueue)) &&
	    (!(tblk->xflag & COMMIT_LAZY) || test_bit(log_FLUSH, &log->flag)
	     || jfs_tlocks_low)) {
		/*
		 * No pageout in progress
		 *
		 * start group commit as its group leader.
		 */
		log->cflag |= logGC_PAGEOUT;

		lmGCwrite(log, 0);
	}

	if (tblk->xflag & COMMIT_LAZY) {
		/*
		 * Lazy transactions can leave now
		 */
		LOGGC_UNLOCK(log);
		return 0;
	}

	/* lmGCwrite gives up LOGGC_LOCK, check again */

	if (tblk->flag & tblkGC_COMMITTED) {
		if (tblk->flag & tblkGC_ERROR)
			rc = -EIO;

		LOGGC_UNLOCK(log);
		return rc;
	}

	/* upcount transaction waiting for completion
	 */
	log->gcrtc++;
	tblk->flag |= tblkGC_READY;

	__SLEEP_COND(tblk->gcwait, (tblk->flag & tblkGC_COMMITTED),
		     LOGGC_LOCK(log), LOGGC_UNLOCK(log));

	/* removed from commit queue */
	if (tblk->flag & tblkGC_ERROR)
		rc = -EIO;

	LOGGC_UNLOCK(log);
	return rc;
}