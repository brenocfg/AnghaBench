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

/* Variables and functions */
 int /*<<< orphan*/  CommitTsCtl ; 
 int /*<<< orphan*/  SimpleLruTruncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SlruScanDirCbReportPresence ; 
 int /*<<< orphan*/  SlruScanDirectory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int TransactionIdToCTsPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteTruncateXlogRec (int,int /*<<< orphan*/ ) ; 

void
TruncateCommitTs(TransactionId oldestXact)
{
	int			cutoffPage;

	/*
	 * The cutoff point is the start of the segment containing oldestXact. We
	 * pass the *page* containing oldestXact to SimpleLruTruncate.
	 */
	cutoffPage = TransactionIdToCTsPage(oldestXact);

	/* Check to see if there's any files that could be removed */
	if (!SlruScanDirectory(CommitTsCtl, SlruScanDirCbReportPresence,
						   &cutoffPage))
		return;					/* nothing to remove */

	/* Write XLOG record */
	WriteTruncateXlogRec(cutoffPage, oldestXact);

	/* Now we can remove the old CommitTs segment(s) */
	SimpleLruTruncate(CommitTsCtl, cutoffPage);
}