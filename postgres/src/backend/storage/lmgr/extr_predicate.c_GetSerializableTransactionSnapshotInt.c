#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VirtualTransactionId ;
struct TYPE_22__ {int /*<<< orphan*/  lastCommitBeforeSnapshot; } ;
struct TYPE_24__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  finishedLink; int /*<<< orphan*/  predicateLocks; int /*<<< orphan*/  pid; int /*<<< orphan*/  xmin; int /*<<< orphan*/  finishedBefore; int /*<<< orphan*/  topXid; int /*<<< orphan*/  possibleUnsafeConflicts; int /*<<< orphan*/  inConflicts; int /*<<< orphan*/  outConflicts; void* commitSeqNo; void* prepareSeqNo; TYPE_1__ SeqNo; int /*<<< orphan*/  vxid; } ;
struct TYPE_23__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_21__ {scalar_t__ WritableSxactCount; int SxactGlobalXminCount; int /*<<< orphan*/  LastSxactCommitSeqNo; int /*<<< orphan*/  SxactGlobalXmin; } ;
typedef  TYPE_2__* Snapshot ;
typedef  TYPE_3__ SERIALIZABLEXACT ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CreateLocalPredicateLockHash () ; 
 TYPE_3__* CreatePredXact () ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_3__* FirstPredXact () ; 
 int /*<<< orphan*/  GET_VXID_FROM_PGPROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* GetSnapshotData (TYPE_2__*) ; 
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 void* InvalidSerCommitSeqNo ; 
 TYPE_3__* InvalidSerializableXact ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MaxBackends ; 
 int /*<<< orphan*/ * MyProc ; 
 int /*<<< orphan*/  MyProcPid ; 
 TYPE_3__* MySerializableXact ; 
 int MyXactDidWrite ; 
 TYPE_3__* NextPredXact (TYPE_3__*) ; 
 int /*<<< orphan*/  OldSerXidSetActiveSerXmin (int /*<<< orphan*/ ) ; 
 TYPE_10__* PredXact ; 
 int /*<<< orphan*/  ProcArrayInstallImportedXmin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  ReleasePredXact (TYPE_3__*) ; 
 int /*<<< orphan*/  SHMQueueElemInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMQueueInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SXACT_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  SerializableXactHashLock ; 
 int /*<<< orphan*/  SetPossibleUnsafeConflict (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SummarizeOldestCommittedSxact () ; 
 int /*<<< orphan*/  SxactIsCommitted (TYPE_3__*) ; 
 int /*<<< orphan*/  SxactIsDoomed (TYPE_3__*) ; 
 int /*<<< orphan*/  SxactIsReadOnly (TYPE_3__*) ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TransactionIdFollows (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ XactReadOnly ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ max_prepared_xacts ; 

__attribute__((used)) static Snapshot
GetSerializableTransactionSnapshotInt(Snapshot snapshot,
									  VirtualTransactionId *sourcevxid,
									  int sourcepid)
{
	PGPROC	   *proc;
	VirtualTransactionId vxid;
	SERIALIZABLEXACT *sxact,
			   *othersxact;

	/* We only do this for serializable transactions.  Once. */
	Assert(MySerializableXact == InvalidSerializableXact);

	Assert(!RecoveryInProgress());

	/*
	 * Since all parts of a serializable transaction must use the same
	 * snapshot, it is too late to establish one after a parallel operation
	 * has begun.
	 */
	if (IsInParallelMode())
		elog(ERROR, "cannot establish serializable snapshot during a parallel operation");

	proc = MyProc;
	Assert(proc != NULL);
	GET_VXID_FROM_PGPROC(vxid, *proc);

	/*
	 * First we get the sxact structure, which may involve looping and access
	 * to the "finished" list to free a structure for use.
	 *
	 * We must hold SerializableXactHashLock when taking/checking the snapshot
	 * to avoid race conditions, for much the same reasons that
	 * GetSnapshotData takes the ProcArrayLock.  Since we might have to
	 * release SerializableXactHashLock to call SummarizeOldestCommittedSxact,
	 * this means we have to create the sxact first, which is a bit annoying
	 * (in particular, an elog(ERROR) in procarray.c would cause us to leak
	 * the sxact).  Consider refactoring to avoid this.
	 */
#ifdef TEST_OLDSERXID
	SummarizeOldestCommittedSxact();
#endif
	LWLockAcquire(SerializableXactHashLock, LW_EXCLUSIVE);
	do
	{
		sxact = CreatePredXact();
		/* If null, push out committed sxact to SLRU summary & retry. */
		if (!sxact)
		{
			LWLockRelease(SerializableXactHashLock);
			SummarizeOldestCommittedSxact();
			LWLockAcquire(SerializableXactHashLock, LW_EXCLUSIVE);
		}
	} while (!sxact);

	/* Get the snapshot, or check that it's safe to use */
	if (!sourcevxid)
		snapshot = GetSnapshotData(snapshot);
	else if (!ProcArrayInstallImportedXmin(snapshot->xmin, sourcevxid))
	{
		ReleasePredXact(sxact);
		LWLockRelease(SerializableXactHashLock);
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("could not import the requested snapshot"),
				 errdetail("The source process with PID %d is not running anymore.",
						   sourcepid)));
	}

	/*
	 * If there are no serializable transactions which are not read-only, we
	 * can "opt out" of predicate locking and conflict checking for a
	 * read-only transaction.
	 *
	 * The reason this is safe is that a read-only transaction can only become
	 * part of a dangerous structure if it overlaps a writable transaction
	 * which in turn overlaps a writable transaction which committed before
	 * the read-only transaction started.  A new writable transaction can
	 * overlap this one, but it can't meet the other condition of overlapping
	 * a transaction which committed before this one started.
	 */
	if (XactReadOnly && PredXact->WritableSxactCount == 0)
	{
		ReleasePredXact(sxact);
		LWLockRelease(SerializableXactHashLock);
		return snapshot;
	}

	/* Maintain serializable global xmin info. */
	if (!TransactionIdIsValid(PredXact->SxactGlobalXmin))
	{
		Assert(PredXact->SxactGlobalXminCount == 0);
		PredXact->SxactGlobalXmin = snapshot->xmin;
		PredXact->SxactGlobalXminCount = 1;
		OldSerXidSetActiveSerXmin(snapshot->xmin);
	}
	else if (TransactionIdEquals(snapshot->xmin, PredXact->SxactGlobalXmin))
	{
		Assert(PredXact->SxactGlobalXminCount > 0);
		PredXact->SxactGlobalXminCount++;
	}
	else
	{
		Assert(TransactionIdFollows(snapshot->xmin, PredXact->SxactGlobalXmin));
	}

	/* Initialize the structure. */
	sxact->vxid = vxid;
	sxact->SeqNo.lastCommitBeforeSnapshot = PredXact->LastSxactCommitSeqNo;
	sxact->prepareSeqNo = InvalidSerCommitSeqNo;
	sxact->commitSeqNo = InvalidSerCommitSeqNo;
	SHMQueueInit(&(sxact->outConflicts));
	SHMQueueInit(&(sxact->inConflicts));
	SHMQueueInit(&(sxact->possibleUnsafeConflicts));
	sxact->topXid = GetTopTransactionIdIfAny();
	sxact->finishedBefore = InvalidTransactionId;
	sxact->xmin = snapshot->xmin;
	sxact->pid = MyProcPid;
	SHMQueueInit(&(sxact->predicateLocks));
	SHMQueueElemInit(&(sxact->finishedLink));
	sxact->flags = 0;
	if (XactReadOnly)
	{
		sxact->flags |= SXACT_FLAG_READ_ONLY;

		/*
		 * Register all concurrent r/w transactions as possible conflicts; if
		 * all of them commit without any outgoing conflicts to earlier
		 * transactions then this snapshot can be deemed safe (and we can run
		 * without tracking predicate locks).
		 */
		for (othersxact = FirstPredXact();
			 othersxact != NULL;
			 othersxact = NextPredXact(othersxact))
		{
			if (!SxactIsCommitted(othersxact)
				&& !SxactIsDoomed(othersxact)
				&& !SxactIsReadOnly(othersxact))
			{
				SetPossibleUnsafeConflict(sxact, othersxact);
			}
		}
	}
	else
	{
		++(PredXact->WritableSxactCount);
		Assert(PredXact->WritableSxactCount <=
			   (MaxBackends + max_prepared_xacts));
	}

	MySerializableXact = sxact;
	MyXactDidWrite = false;		/* haven't written anything yet */

	LWLockRelease(SerializableXactHashLock);

	CreateLocalPredicateLockHash();

	return snapshot;
}