#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tlock {int type; int flag; int /*<<< orphan*/  lock; struct metapage* mp; scalar_t__ next; } ;
struct tblock {int /*<<< orphan*/  synclist; scalar_t__ lsn; scalar_t__ last; scalar_t__ next; scalar_t__ clsn; int /*<<< orphan*/  sb; } ;
struct metapage {int xflag; scalar_t__ nohomeok; scalar_t__ clsn; } ;
struct linelock {scalar_t__ next; } ;
struct jfs_log {int /*<<< orphan*/  count; } ;
typedef  scalar_t__ lid_t ;
struct TYPE_2__ {struct jfs_log* log; } ;

/* Variables and functions */
 int COMMIT_PAGE ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGSYNC_LOCK (struct jfs_log*,unsigned long) ; 
 int /*<<< orphan*/  LOGSYNC_UNLOCK (struct jfs_log*,unsigned long) ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 int /*<<< orphan*/  _metapage_homeok (struct metapage*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hold_metapage (struct metapage*) ; 
 int /*<<< orphan*/  jfs_info (char*,struct tblock*,...) ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logdiff (int,scalar_t__,struct jfs_log*) ; 
 int /*<<< orphan*/  put_metapage (struct metapage*) ; 
 int tlckBTROOT ; 
 int tlckFREEPAGE ; 
 int /*<<< orphan*/  txLockFree (scalar_t__) ; 

__attribute__((used)) static void txUnlock(struct tblock * tblk)
{
	struct tlock *tlck;
	struct linelock *linelock;
	lid_t lid, next, llid, k;
	struct metapage *mp;
	struct jfs_log *log;
	int difft, diffp;
	unsigned long flags;

	jfs_info("txUnlock: tblk = 0x%p", tblk);
	log = JFS_SBI(tblk->sb)->log;

	/*
	 * mark page under tlock homeok (its log has been written):
	 */
	for (lid = tblk->next; lid; lid = next) {
		tlck = lid_to_tlock(lid);
		next = tlck->next;

		jfs_info("unlocking lid = %d, tlck = 0x%p", lid, tlck);

		/* unbind page from tlock */
		if ((mp = tlck->mp) != NULL &&
		    (tlck->type & tlckBTROOT) == 0) {
			assert(mp->xflag & COMMIT_PAGE);

			/* hold buffer
			 */
			hold_metapage(mp);

			assert(mp->nohomeok > 0);
			_metapage_homeok(mp);

			/* inherit younger/larger clsn */
			LOGSYNC_LOCK(log, flags);
			if (mp->clsn) {
				logdiff(difft, tblk->clsn, log);
				logdiff(diffp, mp->clsn, log);
				if (difft > diffp)
					mp->clsn = tblk->clsn;
			} else
				mp->clsn = tblk->clsn;
			LOGSYNC_UNLOCK(log, flags);

			assert(!(tlck->flag & tlckFREEPAGE));

			put_metapage(mp);
		}

		/* insert tlock, and linelock(s) of the tlock if any,
		 * at head of freelist
		 */
		TXN_LOCK();

		llid = ((struct linelock *) & tlck->lock)->next;
		while (llid) {
			linelock = (struct linelock *) lid_to_tlock(llid);
			k = linelock->next;
			txLockFree(llid);
			llid = k;
		}
		txLockFree(lid);

		TXN_UNLOCK();
	}
	tblk->next = tblk->last = 0;

	/*
	 * remove tblock from logsynclist
	 * (allocation map pages inherited lsn of tblk and
	 * has been inserted in logsync list at txUpdateMap())
	 */
	if (tblk->lsn) {
		LOGSYNC_LOCK(log, flags);
		log->count--;
		list_del(&tblk->synclist);
		LOGSYNC_UNLOCK(log, flags);
	}
}