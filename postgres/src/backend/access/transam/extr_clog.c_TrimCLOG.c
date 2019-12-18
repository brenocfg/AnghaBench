#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  nextFullXid; } ;
struct TYPE_6__ {TYPE_1__* shared; } ;
struct TYPE_5__ {int latest_page_number; char** page_buffer; int* page_dirty; } ;

/* Variables and functions */
 int BLCKSZ ; 
 int CLOG_BITS_PER_XACT ; 
 int /*<<< orphan*/  CLogControlLock ; 
 TYPE_2__* ClogCtl ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MemSet (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ShmemVariableCache ; 
 int SimpleLruReadPage (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int TransactionIdToBIndex (int /*<<< orphan*/ ) ; 
 int TransactionIdToByte (int /*<<< orphan*/ ) ; 
 int TransactionIdToPage (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdToPgIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 

void
TrimCLOG(void)
{
	TransactionId xid = XidFromFullTransactionId(ShmemVariableCache->nextFullXid);
	int			pageno = TransactionIdToPage(xid);

	LWLockAcquire(CLogControlLock, LW_EXCLUSIVE);

	/*
	 * Re-Initialize our idea of the latest page number.
	 */
	ClogCtl->shared->latest_page_number = pageno;

	/*
	 * Zero out the remainder of the current clog page.  Under normal
	 * circumstances it should be zeroes already, but it seems at least
	 * theoretically possible that XLOG replay will have settled on a nextXID
	 * value that is less than the last XID actually used and marked by the
	 * previous database lifecycle (since subtransaction commit writes clog
	 * but makes no WAL entry).  Let's just be safe. (We need not worry about
	 * pages beyond the current one, since those will be zeroed when first
	 * used.  For the same reason, there is no need to do anything when
	 * nextFullXid is exactly at a page boundary; and it's likely that the
	 * "current" page doesn't exist yet in that case.)
	 */
	if (TransactionIdToPgIndex(xid) != 0)
	{
		int			byteno = TransactionIdToByte(xid);
		int			bshift = TransactionIdToBIndex(xid) * CLOG_BITS_PER_XACT;
		int			slotno;
		char	   *byteptr;

		slotno = SimpleLruReadPage(ClogCtl, pageno, false, xid);
		byteptr = ClogCtl->shared->page_buffer[slotno] + byteno;

		/* Zero so-far-unused positions in the current byte */
		*byteptr &= (1 << bshift) - 1;
		/* Zero the rest of the page */
		MemSet(byteptr + 1, 0, BLCKSZ - byteno - 1);

		ClogCtl->shared->page_dirty[slotno] = true;
	}

	LWLockRelease(CLogControlLock);
}