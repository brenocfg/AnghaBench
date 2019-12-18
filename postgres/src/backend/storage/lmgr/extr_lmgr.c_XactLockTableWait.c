#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ oper; int /*<<< orphan*/  ctid; int /*<<< orphan*/  rel; } ;
typedef  TYPE_1__ XactLockTableWaitInfo ;
typedef  scalar_t__ XLTW_Oper ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {struct TYPE_5__* previous; TYPE_1__* arg; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  LOCKTAG ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  TYPE_2__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 int ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int RelationIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_LOCKTAG_TRANSACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  SubTransGetTopmostTransaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ XLTW_None ; 
 int /*<<< orphan*/  XactLockTableWaitErrorCb ; 
 TYPE_2__* error_context_stack ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

void
XactLockTableWait(TransactionId xid, Relation rel, ItemPointer ctid,
				  XLTW_Oper oper)
{
	LOCKTAG		tag;
	XactLockTableWaitInfo info;
	ErrorContextCallback callback;
	bool		first = true;

	/*
	 * If an operation is specified, set up our verbose error context
	 * callback.
	 */
	if (oper != XLTW_None)
	{
		Assert(RelationIsValid(rel));
		Assert(ItemPointerIsValid(ctid));

		info.rel = rel;
		info.ctid = ctid;
		info.oper = oper;

		callback.callback = XactLockTableWaitErrorCb;
		callback.arg = &info;
		callback.previous = error_context_stack;
		error_context_stack = &callback;
	}

	for (;;)
	{
		Assert(TransactionIdIsValid(xid));
		Assert(!TransactionIdEquals(xid, GetTopTransactionIdIfAny()));

		SET_LOCKTAG_TRANSACTION(tag, xid);

		(void) LockAcquire(&tag, ShareLock, false, false);

		LockRelease(&tag, ShareLock, false);

		if (!TransactionIdIsInProgress(xid))
			break;

		/*
		 * If the Xid belonged to a subtransaction, then the lock would have
		 * gone away as soon as it was finished; for correct tuple visibility,
		 * the right action is to wait on its parent transaction to go away.
		 * But instead of going levels up one by one, we can just wait for the
		 * topmost transaction to finish with the same end result, which also
		 * incurs less locktable traffic.
		 *
		 * Some uses of this function don't involve tuple visibility -- such
		 * as when building snapshots for logical decoding.  It is possible to
		 * see a transaction in ProcArray before it registers itself in the
		 * locktable.  The topmost transaction in that case is the same xid,
		 * so we try again after a short sleep.  (Don't sleep the first time
		 * through, to avoid slowing down the normal case.)
		 */
		if (!first)
			pg_usleep(1000L);
		first = false;
		xid = SubTransGetTopmostTransaction(xid);
	}

	if (oper != XLTW_None)
		error_context_stack = callback.previous;
}