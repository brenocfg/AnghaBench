#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oldestXid; int /*<<< orphan*/  pageno; } ;
typedef  TYPE_1__ xl_commit_ts_truncate ;
struct TYPE_4__ {int /*<<< orphan*/  mainxid; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_2__ xl_commit_ts_set ;
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int TransactionId ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 scalar_t__ COMMIT_TS_SETTS ; 
 scalar_t__ COMMIT_TS_TRUNCATE ; 
 scalar_t__ COMMIT_TS_ZEROPAGE ; 
 int SizeOfCommitTsSet ; 
 scalar_t__ XLR_INFO_MASK ; 
 char* XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetDataLen (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int* palloc (int) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  timestamptz_to_str (int /*<<< orphan*/ ) ; 

void
commit_ts_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	if (info == COMMIT_TS_ZEROPAGE)
	{
		int			pageno;

		memcpy(&pageno, rec, sizeof(int));
		appendStringInfo(buf, "%d", pageno);
	}
	else if (info == COMMIT_TS_TRUNCATE)
	{
		xl_commit_ts_truncate *trunc = (xl_commit_ts_truncate *) rec;

		appendStringInfo(buf, "pageno %d, oldestXid %u",
						 trunc->pageno, trunc->oldestXid);
	}
	else if (info == COMMIT_TS_SETTS)
	{
		xl_commit_ts_set *xlrec = (xl_commit_ts_set *) rec;
		int			nsubxids;

		appendStringInfo(buf, "set %s/%d for: %u",
						 timestamptz_to_str(xlrec->timestamp),
						 xlrec->nodeid,
						 xlrec->mainxid);
		nsubxids = ((XLogRecGetDataLen(record) - SizeOfCommitTsSet) /
					sizeof(TransactionId));
		if (nsubxids > 0)
		{
			int			i;
			TransactionId *subxids;

			subxids = palloc(sizeof(TransactionId) * nsubxids);
			memcpy(subxids,
				   XLogRecGetData(record) + SizeOfCommitTsSet,
				   sizeof(TransactionId) * nsubxids);
			for (i = 0; i < nsubxids; i++)
				appendStringInfo(buf, ", %u", subxids[i]);
			pfree(subxids);
		}
	}
}