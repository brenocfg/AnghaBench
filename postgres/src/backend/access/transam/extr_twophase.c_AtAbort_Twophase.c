#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  locking_backend; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* MyLockedGxact ; 
 int /*<<< orphan*/  RemoveGXact (TYPE_1__*) ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 

void
AtAbort_Twophase(void)
{
	if (MyLockedGxact == NULL)
		return;

	/*
	 * What to do with the locked global transaction entry?  If we were in the
	 * process of preparing the transaction, but haven't written the WAL
	 * record and state file yet, the transaction must not be considered as
	 * prepared.  Likewise, if we are in the process of finishing an
	 * already-prepared transaction, and fail after having already written the
	 * 2nd phase commit or rollback record to the WAL, the transaction should
	 * not be considered as prepared anymore.  In those cases, just remove the
	 * entry from shared memory.
	 *
	 * Otherwise, the entry must be left in place so that the transaction can
	 * be finished later, so just unlock it.
	 *
	 * If we abort during prepare, after having written the WAL record, we
	 * might not have transferred all locks and other state to the prepared
	 * transaction yet.  Likewise, if we abort during commit or rollback,
	 * after having written the WAL record, we might not have released all the
	 * resources held by the transaction yet.  In those cases, the in-memory
	 * state can be wrong, but it's too late to back out.
	 */
	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
	if (!MyLockedGxact->valid)
		RemoveGXact(MyLockedGxact);
	else
		MyLockedGxact->locking_backend = InvalidBackendId;
	LWLockRelease(TwoPhaseStateLock);

	MyLockedGxact = NULL;
}