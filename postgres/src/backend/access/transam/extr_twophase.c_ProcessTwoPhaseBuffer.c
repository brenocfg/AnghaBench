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
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_3__ {int gidlen; int nsubxacts; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ TwoPhaseFileHeader ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  nextFullXid; } ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  AdvanceNextFullTransactionIdPastXid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_DATA_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int LWLockHeldByMeInMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAXALIGN (int) ; 
 int /*<<< orphan*/  PrepareRedoRemove (int /*<<< orphan*/ ,int) ; 
 char* ReadTwoPhaseFile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RemoveTwoPhaseFile (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ShmemVariableCache ; 
 int /*<<< orphan*/  SubTransSetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidAbort (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidCommit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TransactionIdFollows (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdFollowsOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XidFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XlogReadTwoPhaseData (scalar_t__,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ProcessTwoPhaseBuffer(TransactionId xid,
					  XLogRecPtr prepare_start_lsn,
					  bool fromdisk,
					  bool setParent, bool setNextXid)
{
	FullTransactionId nextFullXid = ShmemVariableCache->nextFullXid;
	TransactionId origNextXid = XidFromFullTransactionId(nextFullXid);
	TransactionId *subxids;
	char	   *buf;
	TwoPhaseFileHeader *hdr;
	int			i;

	Assert(LWLockHeldByMeInMode(TwoPhaseStateLock, LW_EXCLUSIVE));

	if (!fromdisk)
		Assert(prepare_start_lsn != InvalidXLogRecPtr);

	/* Already processed? */
	if (TransactionIdDidCommit(xid) || TransactionIdDidAbort(xid))
	{
		if (fromdisk)
		{
			ereport(WARNING,
					(errmsg("removing stale two-phase state file for transaction %u",
							xid)));
			RemoveTwoPhaseFile(xid, true);
		}
		else
		{
			ereport(WARNING,
					(errmsg("removing stale two-phase state from memory for transaction %u",
							xid)));
			PrepareRedoRemove(xid, true);
		}
		return NULL;
	}

	/* Reject XID if too new */
	if (TransactionIdFollowsOrEquals(xid, origNextXid))
	{
		if (fromdisk)
		{
			ereport(WARNING,
					(errmsg("removing future two-phase state file for transaction %u",
							xid)));
			RemoveTwoPhaseFile(xid, true);
		}
		else
		{
			ereport(WARNING,
					(errmsg("removing future two-phase state from memory for transaction %u",
							xid)));
			PrepareRedoRemove(xid, true);
		}
		return NULL;
	}

	if (fromdisk)
	{
		/* Read and validate file */
		buf = ReadTwoPhaseFile(xid, false);
	}
	else
	{
		/* Read xlog data */
		XlogReadTwoPhaseData(prepare_start_lsn, &buf, NULL);
	}

	/* Deconstruct header */
	hdr = (TwoPhaseFileHeader *) buf;
	if (!TransactionIdEquals(hdr->xid, xid))
	{
		if (fromdisk)
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("corrupted two-phase state file for transaction %u",
							xid)));
		else
			ereport(ERROR,
					(errcode(ERRCODE_DATA_CORRUPTED),
					 errmsg("corrupted two-phase state in memory for transaction %u",
							xid)));
	}

	/*
	 * Examine subtransaction XIDs ... they should all follow main XID, and
	 * they may force us to advance nextFullXid.
	 */
	subxids = (TransactionId *) (buf +
								 MAXALIGN(sizeof(TwoPhaseFileHeader)) +
								 MAXALIGN(hdr->gidlen));
	for (i = 0; i < hdr->nsubxacts; i++)
	{
		TransactionId subxid = subxids[i];

		Assert(TransactionIdFollows(subxid, xid));

		/* update nextFullXid if needed */
		if (setNextXid)
			AdvanceNextFullTransactionIdPastXid(subxid);

		if (setParent)
			SubTransSetParent(subxid, xid);
	}

	return buf;
}