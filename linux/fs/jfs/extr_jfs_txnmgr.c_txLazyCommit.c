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
struct tblock {int flag; int /*<<< orphan*/  gcwait; int /*<<< orphan*/  sb; } ;
struct jfs_log {int /*<<< orphan*/  gclock; int /*<<< orphan*/  gcrtc; } ;
struct TYPE_2__ {scalar_t__ log; } ;

/* Variables and functions */
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int TxBlock ; 
 int /*<<< orphan*/  jfs_info (char*,struct tblock*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int tblkGC_COMMITTED ; 
 int tblkGC_LAZY ; 
 int tblkGC_READY ; 
 int tblkGC_UNLOCKED ; 
 int /*<<< orphan*/  txEnd (struct tblock*) ; 
 int /*<<< orphan*/  txUnlock (struct tblock*) ; 
 int /*<<< orphan*/  txUpdateMap (struct tblock*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static void txLazyCommit(struct tblock * tblk)
{
	struct jfs_log *log;

	while (((tblk->flag & tblkGC_READY) == 0) &&
	       ((tblk->flag & tblkGC_UNLOCKED) == 0)) {
		/* We must have gotten ahead of the user thread
		 */
		jfs_info("jfs_lazycommit: tblk 0x%p not unlocked", tblk);
		yield();
	}

	jfs_info("txLazyCommit: processing tblk 0x%p", tblk);

	txUpdateMap(tblk);

	log = (struct jfs_log *) JFS_SBI(tblk->sb)->log;

	spin_lock_irq(&log->gclock);	// LOGGC_LOCK

	tblk->flag |= tblkGC_COMMITTED;

	if (tblk->flag & tblkGC_READY)
		log->gcrtc--;

	wake_up_all(&tblk->gcwait);	// LOGGC_WAKEUP

	/*
	 * Can't release log->gclock until we've tested tblk->flag
	 */
	if (tblk->flag & tblkGC_LAZY) {
		spin_unlock_irq(&log->gclock);	// LOGGC_UNLOCK
		txUnlock(tblk);
		tblk->flag &= ~tblkGC_LAZY;
		txEnd(tblk - TxBlock);	/* Convert back to tid */
	} else
		spin_unlock_irq(&log->gclock);	// LOGGC_UNLOCK

	jfs_info("txLazyCommit: done: tblk = 0x%p", tblk);
}