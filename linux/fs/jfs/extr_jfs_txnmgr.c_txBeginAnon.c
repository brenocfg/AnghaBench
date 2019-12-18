#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct jfs_log {int /*<<< orphan*/  syncwait; int /*<<< orphan*/  flag; } ;
struct TYPE_6__ {struct jfs_log* log; } ;
struct TYPE_5__ {scalar_t__ tlocksInUse; int /*<<< orphan*/  lowlockwait; } ;
struct TYPE_4__ {int /*<<< orphan*/  txBeginAnon_lockslow; int /*<<< orphan*/  txBeginAnon_barrier; int /*<<< orphan*/  txBeginAnon; } ;

/* Variables and functions */
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 TYPE_3__* JFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  TXN_LOCK () ; 
 int /*<<< orphan*/  TXN_SLEEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TXN_UNLOCK () ; 
 TYPE_2__ TxAnchor ; 
 scalar_t__ TxLockVHWM ; 
 TYPE_1__ TxStat ; 
 int /*<<< orphan*/  log_QUIESCE ; 
 int /*<<< orphan*/  log_SYNCBARRIER ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void txBeginAnon(struct super_block *sb)
{
	struct jfs_log *log;

	log = JFS_SBI(sb)->log;

	TXN_LOCK();
	INCREMENT(TxStat.txBeginAnon);

      retry:
	/*
	 * synchronize with logsync barrier
	 */
	if (test_bit(log_SYNCBARRIER, &log->flag) ||
	    test_bit(log_QUIESCE, &log->flag)) {
		INCREMENT(TxStat.txBeginAnon_barrier);
		TXN_SLEEP(&log->syncwait);
		goto retry;
	}

	/*
	 * Don't begin transaction if we're getting starved for tlocks
	 */
	if (TxAnchor.tlocksInUse > TxLockVHWM) {
		INCREMENT(TxStat.txBeginAnon_lockslow);
		TXN_SLEEP(&TxAnchor.lowlockwait);
		goto retry;
	}
	TXN_UNLOCK();
}