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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AdvanceOldestClogXid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClogCtl ; 
 int /*<<< orphan*/  SimpleLruTruncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SlruScanDirCbReportPresence ; 
 int /*<<< orphan*/  SlruScanDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int TransactionIdToPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteTruncateXlogRec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
TruncateCLOG(TransactionId oldestXact, Oid oldestxid_datoid)
{
	int			cutoffPage;

	/*
	 * The cutoff point is the start of the segment containing oldestXact. We
	 * pass the *page* containing oldestXact to SimpleLruTruncate.
	 */
	cutoffPage = TransactionIdToPage(oldestXact);

	/* Check to see if there's any files that could be removed */
	if (!SlruScanDirectory(ClogCtl, SlruScanDirCbReportPresence, &cutoffPage))
		return;					/* nothing to remove */

	/*
	 * Advance oldestClogXid before truncating clog, so concurrent xact status
	 * lookups can ensure they don't attempt to access truncated-away clog.
	 *
	 * It's only necessary to do this if we will actually truncate away clog
	 * pages.
	 */
	AdvanceOldestClogXid(oldestXact);

	/*
	 * Write XLOG record and flush XLOG to disk. We record the oldest xid
	 * we're keeping information about here so we can ensure that it's always
	 * ahead of clog truncation in case we crash, and so a standby finds out
	 * the new valid xid before the next checkpoint.
	 */
	WriteTruncateXlogRec(cutoffPage, oldestXact, oldestxid_datoid);

	/* Now we can remove the old CLOG segment(s) */
	SimpleLruTruncate(ClogCtl, cutoffPage);
}