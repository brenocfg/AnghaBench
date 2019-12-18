#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_14__ {int /*<<< orphan*/  newestCommitTsXid; int /*<<< orphan*/  oldestCommitTsXid; } ;
struct TYPE_13__ {TYPE_2__* shared; } ;
struct TYPE_9__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  time; } ;
struct TYPE_12__ {TYPE_1__ dataLastCommit; int /*<<< orphan*/  xidLastCommit; int /*<<< orphan*/  commitTsActive; } ;
struct TYPE_11__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  time; } ;
struct TYPE_10__ {scalar_t__* page_buffer; } ;
typedef  int /*<<< orphan*/  RepOriginId ;
typedef  TYPE_3__ CommitTimestampEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommitTsControlLock ; 
 TYPE_6__* CommitTsCtl ; 
 int /*<<< orphan*/  CommitTsLock ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidRepOriginId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_7__* ShmemVariableCache ; 
 int SimpleLruReadPage_ReadOnly (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int SizeOfCommitTimestampEntry ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TransactionIdToCTsEntry (int /*<<< orphan*/ ) ; 
 int TransactionIdToCTsPage (int /*<<< orphan*/ ) ; 
 TYPE_5__* commitTsShared ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_commit_ts_disabled () ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,scalar_t__,int) ; 

bool
TransactionIdGetCommitTsData(TransactionId xid, TimestampTz *ts,
							 RepOriginId *nodeid)
{
	int			pageno = TransactionIdToCTsPage(xid);
	int			entryno = TransactionIdToCTsEntry(xid);
	int			slotno;
	CommitTimestampEntry entry;
	TransactionId oldestCommitTsXid;
	TransactionId newestCommitTsXid;

	if (!TransactionIdIsValid(xid))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("cannot retrieve commit timestamp for transaction %u", xid)));
	else if (!TransactionIdIsNormal(xid))
	{
		/* frozen and bootstrap xids are always committed far in the past */
		*ts = 0;
		if (nodeid)
			*nodeid = 0;
		return false;
	}

	LWLockAcquire(CommitTsLock, LW_SHARED);

	/* Error if module not enabled */
	if (!commitTsShared->commitTsActive)
		error_commit_ts_disabled();

	/*
	 * If we're asked for the cached value, return that.  Otherwise, fall
	 * through to read from SLRU.
	 */
	if (commitTsShared->xidLastCommit == xid)
	{
		*ts = commitTsShared->dataLastCommit.time;
		if (nodeid)
			*nodeid = commitTsShared->dataLastCommit.nodeid;

		LWLockRelease(CommitTsLock);
		return *ts != 0;
	}

	oldestCommitTsXid = ShmemVariableCache->oldestCommitTsXid;
	newestCommitTsXid = ShmemVariableCache->newestCommitTsXid;
	/* neither is invalid, or both are */
	Assert(TransactionIdIsValid(oldestCommitTsXid) == TransactionIdIsValid(newestCommitTsXid));
	LWLockRelease(CommitTsLock);

	/*
	 * Return empty if the requested value is outside our valid range.
	 */
	if (!TransactionIdIsValid(oldestCommitTsXid) ||
		TransactionIdPrecedes(xid, oldestCommitTsXid) ||
		TransactionIdPrecedes(newestCommitTsXid, xid))
	{
		*ts = 0;
		if (nodeid)
			*nodeid = InvalidRepOriginId;
		return false;
	}

	/* lock is acquired by SimpleLruReadPage_ReadOnly */
	slotno = SimpleLruReadPage_ReadOnly(CommitTsCtl, pageno, xid);
	memcpy(&entry,
		   CommitTsCtl->shared->page_buffer[slotno] +
		   SizeOfCommitTimestampEntry * entryno,
		   SizeOfCommitTimestampEntry);

	*ts = entry.time;
	if (nodeid)
		*nodeid = entry.nodeid;

	LWLockRelease(CommitTsControlLock);
	return *ts != 0;
}