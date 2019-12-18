#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  XLTW_Oper ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  xid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MultiXactStatus ;
typedef  TYPE_1__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 int ConditionalXactLockTableWait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoLockModesConflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetMultiXactIdMembers (int /*<<< orphan*/ ,TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HEAP_LOCKED_UPGRADED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_XMAX_IS_LOCKED_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKMODE_from_mxstatus (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XactLockTableWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static bool
Do_MultiXactIdWait(MultiXactId multi, MultiXactStatus status,
				   uint16 infomask, bool nowait,
				   Relation rel, ItemPointer ctid, XLTW_Oper oper,
				   int *remaining)
{
	bool		result = true;
	MultiXactMember *members;
	int			nmembers;
	int			remain = 0;

	/* for pre-pg_upgrade tuples, no need to sleep at all */
	nmembers = HEAP_LOCKED_UPGRADED(infomask) ? -1 :
		GetMultiXactIdMembers(multi, &members, false,
							  HEAP_XMAX_IS_LOCKED_ONLY(infomask));

	if (nmembers >= 0)
	{
		int			i;

		for (i = 0; i < nmembers; i++)
		{
			TransactionId memxid = members[i].xid;
			MultiXactStatus memstatus = members[i].status;

			if (TransactionIdIsCurrentTransactionId(memxid))
			{
				remain++;
				continue;
			}

			if (!DoLockModesConflict(LOCKMODE_from_mxstatus(memstatus),
									 LOCKMODE_from_mxstatus(status)))
			{
				if (remaining && TransactionIdIsInProgress(memxid))
					remain++;
				continue;
			}

			/*
			 * This member conflicts with our multi, so we have to sleep (or
			 * return failure, if asked to avoid waiting.)
			 *
			 * Note that we don't set up an error context callback ourselves,
			 * but instead we pass the info down to XactLockTableWait.  This
			 * might seem a bit wasteful because the context is set up and
			 * tore down for each member of the multixact, but in reality it
			 * should be barely noticeable, and it avoids duplicate code.
			 */
			if (nowait)
			{
				result = ConditionalXactLockTableWait(memxid);
				if (!result)
					break;
			}
			else
				XactLockTableWait(memxid, rel, ctid, oper);
		}

		pfree(members);
	}

	if (remaining)
		*remaining = remain;

	return result;
}