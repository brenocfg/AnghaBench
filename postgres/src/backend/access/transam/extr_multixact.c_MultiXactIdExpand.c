#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* TransactionId ;
struct TYPE_5__ {scalar_t__ status; void* xid; } ;
typedef  scalar_t__ MultiXactStatus ;
typedef  TYPE_1__ MultiXactMember ;
typedef  void* MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int GetMultiXactIdMembers (void*,TYPE_1__**,int,int) ; 
 scalar_t__ ISUPDATE_from_mxstatus (scalar_t__) ; 
 void* MultiXactIdCreateFromMembers (int,TYPE_1__*) ; 
 int /*<<< orphan*/  MultiXactIdIsValid (void*) ; 
 size_t MyBackendId ; 
 void** OldestMemberMXactId ; 
 scalar_t__ TransactionIdDidCommit (void*) ; 
 scalar_t__ TransactionIdEquals (void*,void*) ; 
 scalar_t__ TransactionIdIsInProgress (void*) ; 
 int /*<<< orphan*/  TransactionIdIsValid (void*) ; 
 int /*<<< orphan*/  debug_elog3 (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  debug_elog4 (int /*<<< orphan*/ ,char*,void*,void*) ; 
 int /*<<< orphan*/  debug_elog5 (int /*<<< orphan*/ ,char*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxstatus_to_string (scalar_t__) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

MultiXactId
MultiXactIdExpand(MultiXactId multi, TransactionId xid, MultiXactStatus status)
{
	MultiXactId newMulti;
	MultiXactMember *members;
	MultiXactMember *newMembers;
	int			nmembers;
	int			i;
	int			j;

	AssertArg(MultiXactIdIsValid(multi));
	AssertArg(TransactionIdIsValid(xid));

	/* MultiXactIdSetOldestMember() must have been called already. */
	Assert(MultiXactIdIsValid(OldestMemberMXactId[MyBackendId]));

	debug_elog5(DEBUG2, "Expand: received multi %u, xid %u status %s",
				multi, xid, mxstatus_to_string(status));

	/*
	 * Note: we don't allow for old multis here.  The reason is that the only
	 * caller of this function does a check that the multixact is no longer
	 * running.
	 */
	nmembers = GetMultiXactIdMembers(multi, &members, false, false);

	if (nmembers < 0)
	{
		MultiXactMember member;

		/*
		 * The MultiXactId is obsolete.  This can only happen if all the
		 * MultiXactId members stop running between the caller checking and
		 * passing it to us.  It would be better to return that fact to the
		 * caller, but it would complicate the API and it's unlikely to happen
		 * too often, so just deal with it by creating a singleton MultiXact.
		 */
		member.xid = xid;
		member.status = status;
		newMulti = MultiXactIdCreateFromMembers(1, &member);

		debug_elog4(DEBUG2, "Expand: %u has no members, create singleton %u",
					multi, newMulti);
		return newMulti;
	}

	/*
	 * If the TransactionId is already a member of the MultiXactId with the
	 * same status, just return the existing MultiXactId.
	 */
	for (i = 0; i < nmembers; i++)
	{
		if (TransactionIdEquals(members[i].xid, xid) &&
			(members[i].status == status))
		{
			debug_elog4(DEBUG2, "Expand: %u is already a member of %u",
						xid, multi);
			pfree(members);
			return multi;
		}
	}

	/*
	 * Determine which of the members of the MultiXactId are still of
	 * interest. This is any running transaction, and also any transaction
	 * that grabbed something stronger than just a lock and was committed. (An
	 * update that aborted is of no interest here; and having more than one
	 * update Xid in a multixact would cause errors elsewhere.)
	 *
	 * Removing dead members is not just an optimization: freezing of tuples
	 * whose Xmax are multis depends on this behavior.
	 *
	 * Note we have the same race condition here as above: j could be 0 at the
	 * end of the loop.
	 */
	newMembers = (MultiXactMember *)
		palloc(sizeof(MultiXactMember) * (nmembers + 1));

	for (i = 0, j = 0; i < nmembers; i++)
	{
		if (TransactionIdIsInProgress(members[i].xid) ||
			(ISUPDATE_from_mxstatus(members[i].status) &&
			 TransactionIdDidCommit(members[i].xid)))
		{
			newMembers[j].xid = members[i].xid;
			newMembers[j++].status = members[i].status;
		}
	}

	newMembers[j].xid = xid;
	newMembers[j++].status = status;
	newMulti = MultiXactIdCreateFromMembers(j, newMembers);

	pfree(members);
	pfree(newMembers);

	debug_elog3(DEBUG2, "Expand: returning new multi %u", newMulti);

	return newMulti;
}