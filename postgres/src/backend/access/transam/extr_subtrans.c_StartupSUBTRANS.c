#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_2__ {int /*<<< orphan*/  nextFullXid; } ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MaxTransactionId ; 
 TYPE_1__* ShmemVariableCache ; 
 int /*<<< orphan*/  SubtransControlLock ; 
 int TransactionIdToPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroSUBTRANSPage (int) ; 

void
StartupSUBTRANS(TransactionId oldestActiveXID)
{
	FullTransactionId nextFullXid;
	int			startPage;
	int			endPage;

	/*
	 * Since we don't expect pg_subtrans to be valid across crashes, we
	 * initialize the currently-active page(s) to zeroes during startup.
	 * Whenever we advance into a new page, ExtendSUBTRANS will likewise zero
	 * the new page without regard to whatever was previously on disk.
	 */
	LWLockAcquire(SubtransControlLock, LW_EXCLUSIVE);

	startPage = TransactionIdToPage(oldestActiveXID);
	nextFullXid = ShmemVariableCache->nextFullXid;
	endPage = TransactionIdToPage(XidFromFullTransactionId(nextFullXid));

	while (startPage != endPage)
	{
		(void) ZeroSUBTRANSPage(startPage);
		startPage++;
		/* must account for wraparound */
		if (startPage > TransactionIdToPage(MaxTransactionId))
			startPage = 0;
	}
	(void) ZeroSUBTRANSPage(startPage);

	LWLockRelease(SubtransControlLock);
}