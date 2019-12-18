#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_25__ {int /*<<< orphan*/  t_data; } ;
struct TYPE_21__ {scalar_t__ lastCommitBeforeSnapshot; scalar_t__ earliestOutConflictCommit; } ;
struct TYPE_24__ {TYPE_1__ SeqNo; int /*<<< orphan*/  flags; int /*<<< orphan*/  topXid; int /*<<< orphan*/  inConflicts; } ;
struct TYPE_23__ {TYPE_4__* myXact; } ;
struct TYPE_22__ {int /*<<< orphan*/  xid; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  scalar_t__ SerCommitSeqNo ;
typedef  TYPE_2__ SERIALIZABLEXIDTAG ;
typedef  TYPE_3__ SERIALIZABLEXID ;
typedef  TYPE_4__ SERIALIZABLEXACT ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_5__* HeapTuple ;
typedef  int HTSV_Result ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FlagRWConflict (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 int /*<<< orphan*/  HASH_FIND ; 
#define  HEAPTUPLE_DEAD 132 
#define  HEAPTUPLE_DELETE_IN_PROGRESS 131 
#define  HEAPTUPLE_INSERT_IN_PROGRESS 130 
#define  HEAPTUPLE_LIVE 129 
#define  HEAPTUPLE_RECENTLY_DEAD 128 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (int /*<<< orphan*/ ) ; 
 int HeapTupleSatisfiesVacuum (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidSerCommitSeqNo ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_4__* MySerializableXact ; 
 scalar_t__ OldSerXidGetMinConflictCommitSeqNo (int /*<<< orphan*/ ) ; 
 scalar_t__ RWConflictExists (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SHMQueueEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SXACT_FLAG_DOOMED ; 
 int /*<<< orphan*/  SXACT_FLAG_SUMMARY_CONFLICT_OUT ; 
 int /*<<< orphan*/  SerializableXactHashLock ; 
 int /*<<< orphan*/  SerializableXidHash ; 
 int /*<<< orphan*/  SerializationNeededForRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubTransGetTopmostTransaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SxactHasConflictOut (TYPE_4__*) ; 
 scalar_t__ SxactHasSummaryConflictIn (TYPE_4__*) ; 
 scalar_t__ SxactHasSummaryConflictOut (TYPE_4__*) ; 
 scalar_t__ SxactIsCommitted (TYPE_4__*) ; 
 scalar_t__ SxactIsDoomed (TYPE_4__*) ; 
 int /*<<< orphan*/  SxactIsPrepared (TYPE_4__*) ; 
 scalar_t__ SxactIsReadOnly (TYPE_4__*) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdFollowsOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionXmin ; 
 int /*<<< orphan*/  XidIsConcurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,...) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
CheckForSerializableConflictOut(bool visible, Relation relation,
								HeapTuple tuple, Buffer buffer,
								Snapshot snapshot)
{
	TransactionId xid;
	SERIALIZABLEXIDTAG sxidtag;
	SERIALIZABLEXID *sxid;
	SERIALIZABLEXACT *sxact;
	HTSV_Result htsvResult;

	if (!SerializationNeededForRead(relation, snapshot))
		return;

	/* Check if someone else has already decided that we need to die */
	if (SxactIsDoomed(MySerializableXact))
	{
		ereport(ERROR,
				(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
				 errmsg("could not serialize access due to read/write dependencies among transactions"),
				 errdetail_internal("Reason code: Canceled on identification as a pivot, during conflict out checking."),
				 errhint("The transaction might succeed if retried.")));
	}

	/*
	 * Check to see whether the tuple has been written to by a concurrent
	 * transaction, either to create it not visible to us, or to delete it
	 * while it is visible to us.  The "visible" bool indicates whether the
	 * tuple is visible to us, while HeapTupleSatisfiesVacuum checks what else
	 * is going on with it.
	 */
	htsvResult = HeapTupleSatisfiesVacuum(tuple, TransactionXmin, buffer);
	switch (htsvResult)
	{
		case HEAPTUPLE_LIVE:
			if (visible)
				return;
			xid = HeapTupleHeaderGetXmin(tuple->t_data);
			break;
		case HEAPTUPLE_RECENTLY_DEAD:
			if (!visible)
				return;
			xid = HeapTupleHeaderGetUpdateXid(tuple->t_data);
			break;
		case HEAPTUPLE_DELETE_IN_PROGRESS:
			xid = HeapTupleHeaderGetUpdateXid(tuple->t_data);
			break;
		case HEAPTUPLE_INSERT_IN_PROGRESS:
			xid = HeapTupleHeaderGetXmin(tuple->t_data);
			break;
		case HEAPTUPLE_DEAD:
			return;
		default:

			/*
			 * The only way to get to this default clause is if a new value is
			 * added to the enum type without adding it to this switch
			 * statement.  That's a bug, so elog.
			 */
			elog(ERROR, "unrecognized return value from HeapTupleSatisfiesVacuum: %u", htsvResult);

			/*
			 * In spite of having all enum values covered and calling elog on
			 * this default, some compilers think this is a code path which
			 * allows xid to be used below without initialization. Silence
			 * that warning.
			 */
			xid = InvalidTransactionId;
	}
	Assert(TransactionIdIsValid(xid));
	Assert(TransactionIdFollowsOrEquals(xid, TransactionXmin));

	/*
	 * Find top level xid.  Bail out if xid is too early to be a conflict, or
	 * if it's our own xid.
	 */
	if (TransactionIdEquals(xid, GetTopTransactionIdIfAny()))
		return;
	xid = SubTransGetTopmostTransaction(xid);
	if (TransactionIdPrecedes(xid, TransactionXmin))
		return;
	if (TransactionIdEquals(xid, GetTopTransactionIdIfAny()))
		return;

	/*
	 * Find sxact or summarized info for the top level xid.
	 */
	sxidtag.xid = xid;
	LWLockAcquire(SerializableXactHashLock, LW_EXCLUSIVE);
	sxid = (SERIALIZABLEXID *)
		hash_search(SerializableXidHash, &sxidtag, HASH_FIND, NULL);
	if (!sxid)
	{
		/*
		 * Transaction not found in "normal" SSI structures.  Check whether it
		 * got pushed out to SLRU storage for "old committed" transactions.
		 */
		SerCommitSeqNo conflictCommitSeqNo;

		conflictCommitSeqNo = OldSerXidGetMinConflictCommitSeqNo(xid);
		if (conflictCommitSeqNo != 0)
		{
			if (conflictCommitSeqNo != InvalidSerCommitSeqNo
				&& (!SxactIsReadOnly(MySerializableXact)
					|| conflictCommitSeqNo
					<= MySerializableXact->SeqNo.lastCommitBeforeSnapshot))
				ereport(ERROR,
						(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
						 errmsg("could not serialize access due to read/write dependencies among transactions"),
						 errdetail_internal("Reason code: Canceled on conflict out to old pivot %u.", xid),
						 errhint("The transaction might succeed if retried.")));

			if (SxactHasSummaryConflictIn(MySerializableXact)
				|| !SHMQueueEmpty(&MySerializableXact->inConflicts))
				ereport(ERROR,
						(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
						 errmsg("could not serialize access due to read/write dependencies among transactions"),
						 errdetail_internal("Reason code: Canceled on identification as a pivot, with conflict out to old committed transaction %u.", xid),
						 errhint("The transaction might succeed if retried.")));

			MySerializableXact->flags |= SXACT_FLAG_SUMMARY_CONFLICT_OUT;
		}

		/* It's not serializable or otherwise not important. */
		LWLockRelease(SerializableXactHashLock);
		return;
	}
	sxact = sxid->myXact;
	Assert(TransactionIdEquals(sxact->topXid, xid));
	if (sxact == MySerializableXact || SxactIsDoomed(sxact))
	{
		/* Can't conflict with ourself or a transaction that will roll back. */
		LWLockRelease(SerializableXactHashLock);
		return;
	}

	/*
	 * We have a conflict out to a transaction which has a conflict out to a
	 * summarized transaction.  That summarized transaction must have
	 * committed first, and we can't tell when it committed in relation to our
	 * snapshot acquisition, so something needs to be canceled.
	 */
	if (SxactHasSummaryConflictOut(sxact))
	{
		if (!SxactIsPrepared(sxact))
		{
			sxact->flags |= SXACT_FLAG_DOOMED;
			LWLockRelease(SerializableXactHashLock);
			return;
		}
		else
		{
			LWLockRelease(SerializableXactHashLock);
			ereport(ERROR,
					(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
					 errmsg("could not serialize access due to read/write dependencies among transactions"),
					 errdetail_internal("Reason code: Canceled on conflict out to old pivot."),
					 errhint("The transaction might succeed if retried.")));
		}
	}

	/*
	 * If this is a read-only transaction and the writing transaction has
	 * committed, and it doesn't have a rw-conflict to a transaction which
	 * committed before it, no conflict.
	 */
	if (SxactIsReadOnly(MySerializableXact)
		&& SxactIsCommitted(sxact)
		&& !SxactHasSummaryConflictOut(sxact)
		&& (!SxactHasConflictOut(sxact)
			|| MySerializableXact->SeqNo.lastCommitBeforeSnapshot < sxact->SeqNo.earliestOutConflictCommit))
	{
		/* Read-only transaction will appear to run first.  No conflict. */
		LWLockRelease(SerializableXactHashLock);
		return;
	}

	if (!XidIsConcurrent(xid))
	{
		/* This write was already in our snapshot; no conflict. */
		LWLockRelease(SerializableXactHashLock);
		return;
	}

	if (RWConflictExists(MySerializableXact, sxact))
	{
		/* We don't want duplicate conflict records in the list. */
		LWLockRelease(SerializableXactHashLock);
		return;
	}

	/*
	 * Flag the conflict.  But first, if this conflict creates a dangerous
	 * structure, ereport an error.
	 */
	FlagRWConflict(MySerializableXact, sxact);
	LWLockRelease(SerializableXactHashLock);
}