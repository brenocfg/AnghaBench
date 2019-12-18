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
struct TYPE_4__ {int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ MultiXactMember ;
typedef  int MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int GetMultiXactIdMembers (int,TYPE_1__**,int,int) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsInProgress (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_elog2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug_elog3 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debug_elog4 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

bool
MultiXactIdIsRunning(MultiXactId multi, bool isLockOnly)
{
	MultiXactMember *members;
	int			nmembers;
	int			i;

	debug_elog3(DEBUG2, "IsRunning %u?", multi);

	/*
	 * "false" here means we assume our callers have checked that the given
	 * multi cannot possibly come from a pg_upgraded database.
	 */
	nmembers = GetMultiXactIdMembers(multi, &members, false, isLockOnly);

	if (nmembers <= 0)
	{
		debug_elog2(DEBUG2, "IsRunning: no members");
		return false;
	}

	/*
	 * Checking for myself is cheap compared to looking in shared memory;
	 * return true if any live subtransaction of the current top-level
	 * transaction is a member.
	 *
	 * This is not needed for correctness, it's just a fast path.
	 */
	for (i = 0; i < nmembers; i++)
	{
		if (TransactionIdIsCurrentTransactionId(members[i].xid))
		{
			debug_elog3(DEBUG2, "IsRunning: I (%d) am running!", i);
			pfree(members);
			return true;
		}
	}

	/*
	 * This could be made faster by having another entry point in procarray.c,
	 * walking the PGPROC array only once for all the members.  But in most
	 * cases nmembers should be small enough that it doesn't much matter.
	 */
	for (i = 0; i < nmembers; i++)
	{
		if (TransactionIdIsInProgress(members[i].xid))
		{
			debug_elog4(DEBUG2, "IsRunning: member %d (%u) is running",
						i, members[i].xid);
			pfree(members);
			return true;
		}
	}

	pfree(members);

	debug_elog3(DEBUG2, "IsRunning: %u is not running", multi);

	return false;
}