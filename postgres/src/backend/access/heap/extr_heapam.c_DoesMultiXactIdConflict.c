#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_6__ {int /*<<< orphan*/  hwlock; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  size_t LockTupleMode ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  DoLockModesConflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetMultiXactIdMembers (int /*<<< orphan*/ ,TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HEAP_LOCKED_UPGRADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_XMAX_IS_LOCKED_ONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ ISUPDATE_from_mxstatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKMODE_from_mxstatus (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdDidAbort (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 TYPE_2__* tupleLockExtraInfo ; 

__attribute__((used)) static bool
DoesMultiXactIdConflict(MultiXactId multi, uint16 infomask,
						LockTupleMode lockmode, bool *current_is_member)
{
	int			nmembers;
	MultiXactMember *members;
	bool		result = false;
	LOCKMODE	wanted = tupleLockExtraInfo[lockmode].hwlock;

	if (HEAP_LOCKED_UPGRADED(infomask))
		return false;

	nmembers = GetMultiXactIdMembers(multi, &members, false,
									 HEAP_XMAX_IS_LOCKED_ONLY(infomask));
	if (nmembers >= 0)
	{
		int			i;

		for (i = 0; i < nmembers; i++)
		{
			TransactionId memxid;
			LOCKMODE	memlockmode;

			if (result && (current_is_member == NULL || *current_is_member))
				break;

			memlockmode = LOCKMODE_from_mxstatus(members[i].status);

			/* ignore members from current xact (but track their presence) */
			memxid = members[i].xid;
			if (TransactionIdIsCurrentTransactionId(memxid))
			{
				if (current_is_member != NULL)
					*current_is_member = true;
				continue;
			}
			else if (result)
				continue;

			/* ignore members that don't conflict with the lock we want */
			if (!DoLockModesConflict(memlockmode, wanted))
				continue;

			if (ISUPDATE_from_mxstatus(members[i].status))
			{
				/* ignore aborted updaters */
				if (TransactionIdDidAbort(memxid))
					continue;
			}
			else
			{
				/* ignore lockers-only that are no longer in progress */
				if (!TransactionIdIsInProgress(memxid))
					continue;
			}

			/*
			 * Whatever remains are either live lockers that conflict with our
			 * wanted lock, and updaters that are not aborted.  Those conflict
			 * with what we want.  Set up to return true, but keep going to
			 * look for the current transaction among the multixact members,
			 * if needed.
			 */
			result = true;
		}
		pfree(members);
	}

	return result;
}