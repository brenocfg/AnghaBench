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
typedef  int uint16 ;
typedef  scalar_t__ TransactionId ;
struct TYPE_4__ {scalar_t__ xid; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ MultiXactMember ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int GetMultiXactIdMembers (scalar_t__,TYPE_1__**,int,int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 int HEAP_XMAX_LOCK_ONLY ; 
 int /*<<< orphan*/  ISUPDATE_from_mxstatus (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidTransactionId ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static TransactionId
MultiXactIdGetUpdateXid(TransactionId xmax, uint16 t_infomask)
{
	TransactionId update_xact = InvalidTransactionId;
	MultiXactMember *members;
	int			nmembers;

	Assert(!(t_infomask & HEAP_XMAX_LOCK_ONLY));
	Assert(t_infomask & HEAP_XMAX_IS_MULTI);

	/*
	 * Since we know the LOCK_ONLY bit is not set, this cannot be a multi from
	 * pre-pg_upgrade.
	 */
	nmembers = GetMultiXactIdMembers(xmax, &members, false, false);

	if (nmembers > 0)
	{
		int			i;

		for (i = 0; i < nmembers; i++)
		{
			/* Ignore lockers */
			if (!ISUPDATE_from_mxstatus(members[i].status))
				continue;

			/* there can be at most one updater */
			Assert(update_xact == InvalidTransactionId);
			update_xact = members[i].xid;
#ifndef USE_ASSERT_CHECKING

			/*
			 * in an assert-enabled build, walk the whole array to ensure
			 * there's no other updater.
			 */
			break;
#endif
		}

		pfree(members);
	}

	return update_xact;
}