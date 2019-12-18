#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pageno; int /*<<< orphan*/  oldestXid; } ;
typedef  TYPE_2__ xl_commit_ts_truncate ;
struct TYPE_9__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  mainxid; } ;
typedef  TYPE_3__ xl_commit_ts_set ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int TransactionId ;
struct TYPE_10__ {TYPE_1__* shared; } ;
struct TYPE_7__ {int /*<<< orphan*/  latest_page_number; int /*<<< orphan*/ * page_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdvanceOldestCommitTsXid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COMMIT_TS_SETTS ; 
 scalar_t__ COMMIT_TS_TRUNCATE ; 
 scalar_t__ COMMIT_TS_ZEROPAGE ; 
 int /*<<< orphan*/  CommitTsControlLock ; 
 TYPE_4__* CommitTsCtl ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  SimpleLruTruncate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SimpleLruWritePage (TYPE_4__*,int) ; 
 int SizeOfCommitTsSet ; 
 int /*<<< orphan*/  TransactionTreeSetCommitTsData (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ XLR_INFO_MASK ; 
 int XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetDataLen (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecHasAnyBlockRefs (int /*<<< orphan*/ *) ; 
 int ZeroCommitTsPage (int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int,int) ; 
 int* palloc (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 

void
commit_ts_redo(XLogReaderState *record)
{
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	/* Backup blocks are not used in commit_ts records */
	Assert(!XLogRecHasAnyBlockRefs(record));

	if (info == COMMIT_TS_ZEROPAGE)
	{
		int			pageno;
		int			slotno;

		memcpy(&pageno, XLogRecGetData(record), sizeof(int));

		LWLockAcquire(CommitTsControlLock, LW_EXCLUSIVE);

		slotno = ZeroCommitTsPage(pageno, false);
		SimpleLruWritePage(CommitTsCtl, slotno);
		Assert(!CommitTsCtl->shared->page_dirty[slotno]);

		LWLockRelease(CommitTsControlLock);
	}
	else if (info == COMMIT_TS_TRUNCATE)
	{
		xl_commit_ts_truncate *trunc = (xl_commit_ts_truncate *) XLogRecGetData(record);

		AdvanceOldestCommitTsXid(trunc->oldestXid);

		/*
		 * During XLOG replay, latest_page_number isn't set up yet; insert a
		 * suitable value to bypass the sanity test in SimpleLruTruncate.
		 */
		CommitTsCtl->shared->latest_page_number = trunc->pageno;

		SimpleLruTruncate(CommitTsCtl, trunc->pageno);
	}
	else if (info == COMMIT_TS_SETTS)
	{
		xl_commit_ts_set *setts = (xl_commit_ts_set *) XLogRecGetData(record);
		int			nsubxids;
		TransactionId *subxids;

		nsubxids = ((XLogRecGetDataLen(record) - SizeOfCommitTsSet) /
					sizeof(TransactionId));
		if (nsubxids > 0)
		{
			subxids = palloc(sizeof(TransactionId) * nsubxids);
			memcpy(subxids,
				   XLogRecGetData(record) + SizeOfCommitTsSet,
				   sizeof(TransactionId) * nsubxids);
		}
		else
			subxids = NULL;

		TransactionTreeSetCommitTsData(setts->mainxid, nsubxids, subxids,
									   setts->timestamp, setts->nodeid, true);
		if (subxids)
			pfree(subxids);
	}
	else
		elog(PANIC, "commit_ts_redo: unknown op code %u", info);
}