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
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetTopTransactionIdIfAny () ; 
 scalar_t__ LOCKACQUIRE_NOT_AVAIL ; 
 scalar_t__ LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_LOCKTAG_TRANSACTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  SubTransGetTopmostTransaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

bool
ConditionalXactLockTableWait(TransactionId xid)
{
	LOCKTAG		tag;
	bool		first = true;

	for (;;)
	{
		Assert(TransactionIdIsValid(xid));
		Assert(!TransactionIdEquals(xid, GetTopTransactionIdIfAny()));

		SET_LOCKTAG_TRANSACTION(tag, xid);

		if (LockAcquire(&tag, ShareLock, false, true) == LOCKACQUIRE_NOT_AVAIL)
			return false;

		LockRelease(&tag, ShareLock, false);

		if (!TransactionIdIsInProgress(xid))
			break;

		/* See XactLockTableWait about this case */
		if (!first)
			pg_usleep(1000L);
		first = false;
		xid = SubTransGetTopmostTransaction(xid);
	}

	return true;
}