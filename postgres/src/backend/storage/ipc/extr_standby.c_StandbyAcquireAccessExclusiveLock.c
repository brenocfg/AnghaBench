#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* relOid; void* dbOid; void* xid; } ;
typedef  TYPE_1__ xl_standby_lock ;
typedef  void* TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  locks; void* xid; } ;
typedef  TYPE_2__ RecoveryLockListsEntry ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  LockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  OidIsValid (void*) ; 
 int /*<<< orphan*/  RecoveryLockLists ; 
 int /*<<< orphan*/  SET_LOCKTAG_RELATION (int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ TransactionIdDidAbort (void*) ; 
 scalar_t__ TransactionIdDidCommit (void*) ; 
 int /*<<< orphan*/  TransactionIdIsValid (void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*,void*) ; 
 TYPE_2__* hash_search (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

void
StandbyAcquireAccessExclusiveLock(TransactionId xid, Oid dbOid, Oid relOid)
{
	RecoveryLockListsEntry *entry;
	xl_standby_lock *newlock;
	LOCKTAG		locktag;
	bool		found;

	/* Already processed? */
	if (!TransactionIdIsValid(xid) ||
		TransactionIdDidCommit(xid) ||
		TransactionIdDidAbort(xid))
		return;

	elog(trace_recovery(DEBUG4),
		 "adding recovery lock: db %u rel %u", dbOid, relOid);

	/* dbOid is InvalidOid when we are locking a shared relation. */
	Assert(OidIsValid(relOid));

	/* Create a new list for this xid, if we don't have one already. */
	entry = hash_search(RecoveryLockLists, &xid, HASH_ENTER, &found);
	if (!found)
	{
		entry->xid = xid;
		entry->locks = NIL;
	}

	newlock = palloc(sizeof(xl_standby_lock));
	newlock->xid = xid;
	newlock->dbOid = dbOid;
	newlock->relOid = relOid;
	entry->locks = lappend(entry->locks, newlock);

	SET_LOCKTAG_RELATION(locktag, newlock->dbOid, newlock->relOid);

	(void) LockAcquire(&locktag, AccessExclusiveLock, true, false);
}