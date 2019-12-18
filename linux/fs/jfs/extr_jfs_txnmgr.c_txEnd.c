#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tid_t ;
struct tblock {int flag; scalar_t__ next; int /*<<< orphan*/  sb; int /*<<< orphan*/  waitor; } ;
struct jfs_log {scalar_t__ active; scalar_t__ lsn; int /*<<< orphan*/  syncwait; int /*<<< orphan*/  flag; int /*<<< orphan*/  gclock; } ;
struct TYPE_4__ {struct jfs_log* log; } ;
struct TYPE_3__ {scalar_t__ freetid; int /*<<< orphan*/  freewait; } ;

/* Variables and functions */
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 int /*<<< orphan*/  TXN_WAKEUP (int /*<<< orphan*/ *) ; 
 TYPE_1__ TxAnchor ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_info (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  jfs_syncpt (struct jfs_log*,int) ; 
 int /*<<< orphan*/  log_FLUSH ; 
 int /*<<< orphan*/  log_SYNCBARRIER ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int tblkGC_LAZY ; 
 int tblkGC_UNLOCKED ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tblock* tid_to_tblock (scalar_t__) ; 

void txEnd(tid_t tid)
{
	struct tblock *tblk = tid_to_tblock(tid);
	struct jfs_log *log;

	jfs_info("txEnd: tid = %d", tid);
	TXN_LOCK();

	/*
	 * wakeup transactions waiting on the page locked
	 * by the current transaction
	 */
	TXN_WAKEUP(&tblk->waitor);

	log = JFS_SBI(tblk->sb)->log;

	/*
	 * Lazy commit thread can't free this guy until we mark it UNLOCKED,
	 * otherwise, we would be left with a transaction that may have been
	 * reused.
	 *
	 * Lazy commit thread will turn off tblkGC_LAZY before calling this
	 * routine.
	 */
	if (tblk->flag & tblkGC_LAZY) {
		jfs_info("txEnd called w/lazy tid: %d, tblk = 0x%p", tid, tblk);
		TXN_UNLOCK();

		spin_lock_irq(&log->gclock);	// LOGGC_LOCK
		tblk->flag |= tblkGC_UNLOCKED;
		spin_unlock_irq(&log->gclock);	// LOGGC_UNLOCK
		return;
	}

	jfs_info("txEnd: tid: %d, tblk = 0x%p", tid, tblk);

	assert(tblk->next == 0);

	/*
	 * insert tblock back on freelist
	 */
	tblk->next = TxAnchor.freetid;
	TxAnchor.freetid = tid;

	/*
	 * mark the tblock not active
	 */
	if (--log->active == 0) {
		clear_bit(log_FLUSH, &log->flag);

		/*
		 * synchronize with logsync barrier
		 */
		if (test_bit(log_SYNCBARRIER, &log->flag)) {
			TXN_UNLOCK();

			/* write dirty metadata & forward log syncpt */
			jfs_syncpt(log, 1);

			jfs_info("log barrier off: 0x%x", log->lsn);

			/* enable new transactions start */
			clear_bit(log_SYNCBARRIER, &log->flag);

			/* wakeup all waitors for logsync barrier */
			TXN_WAKEUP(&log->syncwait);

			goto wakeup;
		}
	}

	TXN_UNLOCK();
wakeup:
	/*
	 * wakeup all waitors for a free tblock
	 */
	TXN_WAKEUP(&TxAnchor.freewait);
}