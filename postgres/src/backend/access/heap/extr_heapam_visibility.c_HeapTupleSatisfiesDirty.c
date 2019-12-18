#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* TransactionId ;
struct TYPE_17__ {scalar_t__ t_tableOid; int /*<<< orphan*/  t_self; TYPE_2__* t_data; } ;
struct TYPE_16__ {int t_infomask; } ;
struct TYPE_15__ {void* xmax; void* xmin; int /*<<< orphan*/  speculativeToken; } ;
typedef  TYPE_1__* Snapshot ;
typedef  TYPE_2__* HeapTupleHeader ;
typedef  TYPE_3__* HeapTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int HEAP_MOVED_IN ; 
 int HEAP_MOVED_OFF ; 
 int HEAP_XMAX_COMMITTED ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 int HEAP_XMIN_COMMITTED ; 
 int HEAP_XMIN_INVALID ; 
 void* HeapTupleGetUpdateXid (TYPE_2__*) ; 
 void* HeapTupleHeaderGetRawXmax (TYPE_2__*) ; 
 void* HeapTupleHeaderGetRawXmin (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetSpeculativeToken (TYPE_2__*) ; 
 void* HeapTupleHeaderGetXvac (TYPE_2__*) ; 
 scalar_t__ HeapTupleHeaderIsSpeculative (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderXminCommitted (TYPE_2__*) ; 
 scalar_t__ HeapTupleHeaderXminInvalid (TYPE_2__*) ; 
 scalar_t__ InvalidOid ; 
 void* InvalidTransactionId ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetHintBits (TYPE_2__*,int /*<<< orphan*/ ,int,void*) ; 
 scalar_t__ TransactionIdDidCommit (void*) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (void*) ; 
 scalar_t__ TransactionIdIsInProgress (void*) ; 
 int TransactionIdIsValid (void*) ; 

__attribute__((used)) static bool
HeapTupleSatisfiesDirty(HeapTuple htup, Snapshot snapshot,
						Buffer buffer)
{
	HeapTupleHeader tuple = htup->t_data;

	Assert(ItemPointerIsValid(&htup->t_self));
	Assert(htup->t_tableOid != InvalidOid);

	snapshot->xmin = snapshot->xmax = InvalidTransactionId;
	snapshot->speculativeToken = 0;

	if (!HeapTupleHeaderXminCommitted(tuple))
	{
		if (HeapTupleHeaderXminInvalid(tuple))
			return false;

		/* Used by pre-9.0 binary upgrades */
		if (tuple->t_infomask & HEAP_MOVED_OFF)
		{
			TransactionId xvac = HeapTupleHeaderGetXvac(tuple);

			if (TransactionIdIsCurrentTransactionId(xvac))
				return false;
			if (!TransactionIdIsInProgress(xvac))
			{
				if (TransactionIdDidCommit(xvac))
				{
					SetHintBits(tuple, buffer, HEAP_XMIN_INVALID,
								InvalidTransactionId);
					return false;
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
					return false;
				if (TransactionIdDidCommit(xvac))
					SetHintBits(tuple, buffer, HEAP_XMIN_COMMITTED,
								InvalidTransactionId);
				else
				{
					SetHintBits(tuple, buffer, HEAP_XMIN_INVALID,
								InvalidTransactionId);
					return false;
				}
			}
		}
		else if (TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetRawXmin(tuple)))
		{
			if (tuple->t_infomask & HEAP_XMAX_INVALID)	/* xid invalid */
				return true;

			if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))	/* not deleter */
				return true;

			if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
			{
				TransactionId xmax;

				xmax = HeapTupleGetUpdateXid(tuple);

				/* not LOCKED_ONLY, so it has to have an xmax */
				Assert(TransactionIdIsValid(xmax));

				/* updating subtransaction must have aborted */
				if (!TransactionIdIsCurrentTransactionId(xmax))
					return true;
				else
					return false;
			}

			if (!TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetRawXmax(tuple)))
			{
				/* deleting subtransaction must have aborted */
				SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
							InvalidTransactionId);
				return true;
			}

			return false;
		}
		else if (TransactionIdIsInProgress(HeapTupleHeaderGetRawXmin(tuple)))
		{
			/*
			 * Return the speculative token to caller.  Caller can worry about
			 * xmax, since it requires a conclusively locked row version, and
			 * a concurrent update to this tuple is a conflict of its
			 * purposes.
			 */
			if (HeapTupleHeaderIsSpeculative(tuple))
			{
				snapshot->speculativeToken =
					HeapTupleHeaderGetSpeculativeToken(tuple);

				Assert(snapshot->speculativeToken != 0);
			}

			snapshot->xmin = HeapTupleHeaderGetRawXmin(tuple);
			/* XXX shouldn't we fall through to look at xmax? */
			return true;		/* in insertion by other */
		}
		else if (TransactionIdDidCommit(HeapTupleHeaderGetRawXmin(tuple)))
			SetHintBits(tuple, buffer, HEAP_XMIN_COMMITTED,
						HeapTupleHeaderGetRawXmin(tuple));
		else
		{
			/* it must have aborted or crashed */
			SetHintBits(tuple, buffer, HEAP_XMIN_INVALID,
						InvalidTransactionId);
			return false;
		}
	}

	/* by here, the inserting transaction has committed */

	if (tuple->t_infomask & HEAP_XMAX_INVALID)	/* xid invalid or aborted */
		return true;

	if (tuple->t_infomask & HEAP_XMAX_COMMITTED)
	{
		if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			return true;
		return false;			/* updated by other */
	}

	if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
	{
		TransactionId xmax;

		if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			return true;

		xmax = HeapTupleGetUpdateXid(tuple);

		/* not LOCKED_ONLY, so it has to have an xmax */
		Assert(TransactionIdIsValid(xmax));

		if (TransactionIdIsCurrentTransactionId(xmax))
			return false;
		if (TransactionIdIsInProgress(xmax))
		{
			snapshot->xmax = xmax;
			return true;
		}
		if (TransactionIdDidCommit(xmax))
			return false;
		/* it must have aborted or crashed */
		return true;
	}

	if (TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetRawXmax(tuple)))
	{
		if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			return true;
		return false;
	}

	if (TransactionIdIsInProgress(HeapTupleHeaderGetRawXmax(tuple)))
	{
		if (!HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
			snapshot->xmax = HeapTupleHeaderGetRawXmax(tuple);
		return true;
	}

	if (!TransactionIdDidCommit(HeapTupleHeaderGetRawXmax(tuple)))
	{
		/* it must have aborted or crashed */
		SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
					InvalidTransactionId);
		return true;
	}

	/* xmax transaction committed */

	if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
	{
		SetHintBits(tuple, buffer, HEAP_XMAX_INVALID,
					InvalidTransactionId);
		return true;
	}

	SetHintBits(tuple, buffer, HEAP_XMAX_COMMITTED,
				HeapTupleHeaderGetRawXmax(tuple));
	return false;				/* updated by other */
}