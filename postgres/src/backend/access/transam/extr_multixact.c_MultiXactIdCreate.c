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
typedef  void* TransactionId ;
struct TYPE_4__ {scalar_t__ status; void* xid; } ;
typedef  scalar_t__ MultiXactStatus ;
typedef  TYPE_1__ MultiXactMember ;
typedef  int /*<<< orphan*/  MultiXactId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  MultiXactIdCreateFromMembers (int,TYPE_1__*) ; 
 int MultiXactIdIsValid (int /*<<< orphan*/ ) ; 
 size_t MyBackendId ; 
 int /*<<< orphan*/ * OldestMemberMXactId ; 
 int /*<<< orphan*/  TransactionIdEquals (void*,void*) ; 
 int /*<<< orphan*/  TransactionIdIsValid (void*) ; 
 int /*<<< orphan*/  debug_elog3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxid_to_string (int /*<<< orphan*/ ,int,TYPE_1__*) ; 

MultiXactId
MultiXactIdCreate(TransactionId xid1, MultiXactStatus status1,
				  TransactionId xid2, MultiXactStatus status2)
{
	MultiXactId newMulti;
	MultiXactMember members[2];

	AssertArg(TransactionIdIsValid(xid1));
	AssertArg(TransactionIdIsValid(xid2));

	Assert(!TransactionIdEquals(xid1, xid2) || (status1 != status2));

	/* MultiXactIdSetOldestMember() must have been called already. */
	Assert(MultiXactIdIsValid(OldestMemberMXactId[MyBackendId]));

	/*
	 * Note: unlike MultiXactIdExpand, we don't bother to check that both XIDs
	 * are still running.  In typical usage, xid2 will be our own XID and the
	 * caller just did a check on xid1, so it'd be wasted effort.
	 */

	members[0].xid = xid1;
	members[0].status = status1;
	members[1].xid = xid2;
	members[1].status = status2;

	newMulti = MultiXactIdCreateFromMembers(2, members);

	debug_elog3(DEBUG2, "Create: %s",
				mxid_to_string(newMulti, 2, members));

	return newMulti;
}