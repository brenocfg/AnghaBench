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
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  ip; struct metapage* mp; scalar_t__ next; } ;
struct tblock {int /*<<< orphan*/  sb; scalar_t__ last; scalar_t__ next; } ;
struct metapage {int xflag; scalar_t__ lsn; scalar_t__ lid; } ;
typedef  scalar_t__ lid_t ;
struct TYPE_2__ {scalar_t__ xtlid; } ;

/* Variables and functions */
 int COMMIT_PAGE ; 
 TYPE_1__* JFS_IP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LogSyncRelease (struct metapage*) ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txLockFree (scalar_t__) ; 

void txAbort(tid_t tid, int dirty)
{
	lid_t lid, next;
	struct metapage *mp;
	struct tblock *tblk = tid_to_tblock(tid);
	struct tlock *tlck;

	/*
	 * free tlocks of the transaction
	 */
	for (lid = tblk->next; lid; lid = next) {
		tlck = lid_to_tlock(lid);
		next = tlck->next;
		mp = tlck->mp;
		JFS_IP(tlck->ip)->xtlid = 0;

		if (mp) {
			mp->lid = 0;

			/*
			 * reset lsn of page to avoid logwarap:
			 *
			 * (page may have been previously committed by another
			 * transaction(s) but has not been paged, i.e.,
			 * it may be on logsync list even though it has not
			 * been logged for the current tx.)
			 */
			if (mp->xflag & COMMIT_PAGE && mp->lsn)
				LogSyncRelease(mp);
		}
		/* insert tlock at head of freelist */
		TXN_LOCK();
		txLockFree(lid);
		TXN_UNLOCK();
	}

	/* caller will free the transaction block */

	tblk->next = tblk->last = 0;

	/*
	 * mark filesystem dirty
	 */
	if (dirty)
		jfs_error(tblk->sb, "\n");

	return;
}