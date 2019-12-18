#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  relOid; int /*<<< orphan*/  dbOid; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ xl_standby_lock ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKTAG ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LockRelease (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_LOCKTAG_RELATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
StandbyReleaseLockList(List *locks)
{
	while (locks)
	{
		xl_standby_lock *lock = (xl_standby_lock *) linitial(locks);
		LOCKTAG		locktag;

		elog(trace_recovery(DEBUG4),
			 "releasing recovery lock: xid %u db %u rel %u",
			 lock->xid, lock->dbOid, lock->relOid);
		SET_LOCKTAG_RELATION(locktag, lock->dbOid, lock->relOid);
		if (!LockRelease(&locktag, AccessExclusiveLock, true))
		{
			elog(LOG,
				 "RecoveryLockLists contains entry for lock no longer recorded by lock manager: xid %u database %u relation %u",
				 lock->xid, lock->dbOid, lock->relOid);
			Assert(false);
		}
		pfree(lock);
		locks = list_delete_first(locks);
	}
}