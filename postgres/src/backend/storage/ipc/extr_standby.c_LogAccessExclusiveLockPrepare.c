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

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTransactionId () ; 

void
LogAccessExclusiveLockPrepare(void)
{
	/*
	 * Ensure that a TransactionId has been assigned to this transaction, for
	 * two reasons, both related to lock release on the standby. First, we
	 * must assign an xid so that RecordTransactionCommit() and
	 * RecordTransactionAbort() do not optimise away the transaction
	 * completion record which recovery relies upon to release locks. It's a
	 * hack, but for a corner case not worth adding code for into the main
	 * commit path. Second, we must assign an xid before the lock is recorded
	 * in shared memory, otherwise a concurrently executing
	 * GetRunningTransactionLocks() might see a lock associated with an
	 * InvalidTransactionId which we later assert cannot happen.
	 */
	(void) GetCurrentTransactionId();
}