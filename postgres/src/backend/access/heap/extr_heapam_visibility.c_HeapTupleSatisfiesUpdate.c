#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_15__ {scalar_t__ t_tableOid; int /*<<< orphan*/  t_self; TYPE_1__* t_data; } ;
struct TYPE_14__ {int t_infomask; int /*<<< orphan*/  t_ctid; } ;
typedef  int /*<<< orphan*/  TM_Result ;
typedef  TYPE_1__* HeapTupleHeader ;
typedef  TYPE_2__* HeapTuple ;
typedef  scalar_t__ CommandId ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ HEAP_LOCKED_UPGRADED (int) ; 
 int HEAP_MOVED_IN ; 
 int HEAP_MOVED_OFF ; 
 int HEAP_XMAX_COMMITTED ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 int HEAP_XMIN_COMMITTED ; 
 int HEAP_XMIN_INVALID ; 
 int /*<<< orphan*/  HeapTupleGetUpdateXid (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderGetCmax (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderGetCmin (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmax (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmin (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXvac (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderIndicatesMovedPartitions (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderXminCommitted (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderXminInvalid (TYPE_1__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ MultiXactIdIsRunning (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetHintBits (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TM_BeingModified ; 
 int /*<<< orphan*/  TM_Deleted ; 
 int /*<<< orphan*/  TM_Invisible ; 
 int /*<<< orphan*/  TM_Ok ; 
 int /*<<< orphan*/  TM_SelfModified ; 
 int /*<<< orphan*/  TM_Updated ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 

TM_Result
HeapTupleSatisfiesUpdate(HeapTuple htup, CommandId curcid,
						 Buffer buffer)
{
	HeapTupleHeader tuple = htup->t_data;

	Assert(ItemPointerIsValid(&htup->t_self));
	Assert(htup->t_tableOid != InvalidOid);

	if (!HeapTupleHeaderXminCommitted(tuple))
	{
		if (HeapTupleHeaderXminInvalid(tuple))
			return TM_Invisible;

		/* Used by pre-9.0 binary upgrades */
		if (tuple->t_infomask & HEAP_MOVED_OFF)
		{
			TransactionId xvac = HeapTupleHeaderGetXvac(tuple);

			if (TransactionIdIsCurrentTransactionId(xvac))
				return TM_Invisible;
			if (!TransactionIdIsInProgress(xvac))
			{
				if (TransactionIdDidCommit(xvac))
				{
					SetHintBits(tuple, buffer, HEAP_XMIN_INVALID,
								InvalidTransactionId);
					return TM_Invisible;
				}
				SetHintBits(tuple, buffer, HEAP_XMIN_COMMITTED,
							InvalidTransactionId);
			}
		}
		/* Used by pre-9.0 binary upgrades */
		else if (tuple->t_infomask & HEAP_MOVED_IN)
		{
			TransactionId xvac = HeapTupleHeaderGetXvac(tuple);

			if (!TransactionIdIsCurrentTransactionId(xvac))
			{
				if (TransactionIdIsInProgress(xvac))
					return TM_Invisible;
				if (TransactionIdDidCommit(xvac))
					SetHintBits(tuple, buffer, HEAP_XMIN_COMMITTED,
								InvalidTransactionId);
				else
				{
					SetHintBits(tuple, buffer, HEAP_XMIN_INVALID,
								InvalidTransactionId);
					return TM_Invisible;
				}
			}
		}
		else if (TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetRawXmin(tuple)))
		{
			if (HeapTupleHeaderGetCmin(tuple) >= curcid)
				return TM_Invisible;	/* inserted after scan started */

			if (tuple->t_infomask & HEAP_XMAX_INVALID)	/* xid invalid */
				return TM_Ok;

			if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			{
				TransactionId xmax;

				xmax = HeapTupleHeaderGetRawXmax(tuple);

				/*
				 * Careful here: even though this tuple was created by our own
				 * transaction, it might be locked by other transactions, if
				 * the original version was key-share locked when we updated
				 * it.
				 */

				if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
				{
					if (MultiXactIdIsRunning(xmax, true))
						return TM_BeingModified;
					else
						return TM_Ok;
				}

				/*
				 * If the locker is gone, then there is nothing of interest
				 * left in this Xmax; otherwise, report the tuple as
				 * locked/updated.
				 */
				if (!TransactionIdIsInProgress(xmax))
					return TM_Ok;
				return TM_BeingModified;
			}

			if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
			{
				TransactionId xmax;

				xmax = HeapTupleGetUpdateXid(tuple);

				/* not LOCKED_ONLY, so it has to have an xmax */
				Assert(TransactionIdIsValid(xmax));

				/* deleting subtransaction must have aborted */
				if (!TransactionIdIsCurrentTransactionId(xmax))
				{
					if (MultiXactIdIsRunning(HeapTupleHeaderGetRawXmax(tuple),
											 false))
						return TM_BeingModified;
					return TM_Ok;
				}
				else
				{
					if (HeapTupleHeaderGetCmax(tuple) >= curcid)
						return TM_SelfModified; /* updated after scan started */
					else
						return TM_Invisible;	/* updated before scan started */
				}
			}

			if (!TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetRawXmax(tuple)))
			{
				/* deleting subtransaction must have aborted */
				SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
							InvalidTransactionId);
				return TM_Ok;
			}

			if (HeapTupleHeaderGetCmax(tuple) >= curcid)
				return TM_SelfModified; /* updated after scan started */
			else
				return TM_Invisible;	/* updated before scan started */
		}
		else if (TransactionIdIsInProgress(HeapTupleHeaderGetRawXmin(tuple)))
			return TM_Invisible;
		else if (TransactionIdDidCommit(HeapTupleHeaderGetRawXmin(tuple)))
			SetHintBits(tuple, buffer, HEAP_XMIN_COMMITTED,
						HeapTupleHeaderGetRawXmin(tuple));
		else
		{
			/* it must have aborted or crashed */
			SetHintBits(tuple, buffer, HEAP_XMIN_INVALID,
						InvalidTransactionId);
			return TM_Invisible;
		}
	}

	/* by here, the inserting transaction has committed */

	if (tuple->t_infomask & HEAP_XMAX_INVALID)	/* xid invalid or aborted */
		return TM_Ok;

	if (tuple->t_infomask & HEAP_XMAX_COMMITTED)
	{
		if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			return TM_Ok;
		if (!ItemPointerEquals(&htup->t_self, &tuple->t_ctid) ||
			HeapTupleHeaderIndicatesMovedPartitions(tuple))
			return TM_Updated;	/* updated by other */
		else
			return TM_Deleted;	/* deleted by other */
	}

	if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
	{
		TransactionId xmax;

		if (HEAP_LOCKED_UPGRADED(tuple->t_infomask))
			return TM_Ok;

		if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
		{
			if (MultiXactIdIsRunning(HeapTupleHeaderGetRawXmax(tuple), true))
				return TM_BeingModified;

			SetHintBits(tuple, buffer, HEAP_XMAX_INVALID, InvalidTransactionId);
			return TM_Ok;
		}

		xmax = HeapTupleGetUpdateXid(tuple);
		if (!TransactionIdIsValid(xmax))
		{
			if (MultiXactIdIsRunning(HeapTupleHeaderGetRawXmax(tuple), false))
				return TM_BeingModified;
		}

		/* not LOCKED_ONLY, so it has to have an xmax */
		Assert(TransactionIdIsValid(xmax));

		if (TransactionIdIsCurrentTransactionId(xmax))
		{
			if (HeapTupleHeaderGetCmax(tuple) >= curcid)
				return TM_SelfModified; /* updated after scan started */
			else
				return TM_Invisible;	/* updated before scan started */
		}

		if (MultiXactIdIsRunning(HeapTupleHeaderGetRawXmax(tuple), false))
			return TM_BeingModified;

		if (TransactionIdDidCommit(xmax))
		{
			if (!ItemPointerEquals(&htup->t_self, &tuple->t_ctid) ||
				HeapTupleHeaderIndicatesMovedPartitions(tuple))
				return TM_Updated;
			else
				return TM_Deleted;
		}

		/*
		 * By here, the update in the Xmax is either aborted or crashed, but
		 * what about the other members?
		 */

		if (!MultiXactIdIsRunning(HeapTupleHeaderGetRawXmax(tuple), false))
		{
			/*
			 * There's no member, even just a locker, alive anymore, so we can
			 * mark the Xmax as invalid.
			 */
			SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
						InvalidTransactionId);
			return TM_Ok;
		}
		else
		{
			/* There are lockers running */
			return TM_BeingModified;
		}
	}

	if (TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetRawXmax(tuple)))
	{
		if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			return TM_BeingModified;
		if (HeapTupleHeaderGetCmax(tuple) >= curcid)
			return TM_SelfModified; /* updated after scan started */
		else
			return TM_Invisible;	/* updated before scan started */
	}

	if (TransactionIdIsInProgress(HeapTupleHeaderGetRawXmax(tuple)))
		return TM_BeingModified;

	if (!TransactionIdDidCommit(HeapTupleHeaderGetRawXmax(tuple)))
	{
		/* it must have aborted or crashed */
		SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
					InvalidTransactionId);
		return TM_Ok;
	}

	/* xmax transaction committed */

	if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
	{
		SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
					InvalidTransactionId);
		return TM_Ok;
	}

	SetHintBits(tuple, buffer, HEAP_XMAX_COMMITTED,
				HeapTupleHeaderGetRawXmax(tuple));
	if (!ItemPointerEquals(&htup->t_self, &tuple->t_ctid) ||
		HeapTupleHeaderIndicatesMovedPartitions(tuple))
		return TM_Updated;		/* updated by other */
	else
		return TM_Deleted;		/* deleted by other */
}