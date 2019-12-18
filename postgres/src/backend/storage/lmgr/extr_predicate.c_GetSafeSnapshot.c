#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  possibleUnsafeConflicts; } ;
typedef  int /*<<< orphan*/  Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  GetSerializableTransactionSnapshotInt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidPid ; 
 TYPE_1__* InvalidSerializableXact ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* MySerializableXact ; 
 int /*<<< orphan*/  ProcWaitForSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleasePredicateLocks (int,int) ; 
 scalar_t__ SHMQueueEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SXACT_FLAG_DEFERRABLE_WAITING ; 
 int /*<<< orphan*/  SerializableXactHashLock ; 
 int SxactIsROSafe (TYPE_1__*) ; 
 scalar_t__ SxactIsROUnsafe (TYPE_1__*) ; 
 int /*<<< orphan*/  WAIT_EVENT_SAFE_SNAPSHOT ; 
 scalar_t__ XactDeferrable ; 
 scalar_t__ XactReadOnly ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static Snapshot
GetSafeSnapshot(Snapshot origSnapshot)
{
	Snapshot	snapshot;

	Assert(XactReadOnly && XactDeferrable);

	while (true)
	{
		/*
		 * GetSerializableTransactionSnapshotInt is going to call
		 * GetSnapshotData, so we need to provide it the static snapshot area
		 * our caller passed to us.  The pointer returned is actually the same
		 * one passed to it, but we avoid assuming that here.
		 */
		snapshot = GetSerializableTransactionSnapshotInt(origSnapshot,
														 NULL, InvalidPid);

		if (MySerializableXact == InvalidSerializableXact)
			return snapshot;	/* no concurrent r/w xacts; it's safe */

		LWLockAcquire(SerializableXactHashLock, LW_EXCLUSIVE);

		/*
		 * Wait for concurrent transactions to finish. Stop early if one of
		 * them marked us as conflicted.
		 */
		MySerializableXact->flags |= SXACT_FLAG_DEFERRABLE_WAITING;
		while (!(SHMQueueEmpty(&MySerializableXact->possibleUnsafeConflicts) ||
				 SxactIsROUnsafe(MySerializableXact)))
		{
			LWLockRelease(SerializableXactHashLock);
			ProcWaitForSignal(WAIT_EVENT_SAFE_SNAPSHOT);
			LWLockAcquire(SerializableXactHashLock, LW_EXCLUSIVE);
		}
		MySerializableXact->flags &= ~SXACT_FLAG_DEFERRABLE_WAITING;

		if (!SxactIsROUnsafe(MySerializableXact))
		{
			LWLockRelease(SerializableXactHashLock);
			break;				/* success */
		}

		LWLockRelease(SerializableXactHashLock);

		/* else, need to retry... */
		ereport(DEBUG2,
				(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
				 errmsg("deferrable snapshot was unsafe; trying a new one")));
		ReleasePredicateLocks(false, false);
	}

	/*
	 * Now we have a safe snapshot, so we don't need to do any further checks.
	 */
	Assert(SxactIsROSafe(MySerializableXact));
	ReleasePredicateLocks(false, true);

	return snapshot;
}