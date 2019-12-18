#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* TransactionId ;
struct TYPE_10__ {int t_infomask; } ;
struct TYPE_9__ {void* xid; } ;
typedef  TYPE_1__ MultiXactMember ;
typedef  void* MultiXactId ;
typedef  TYPE_2__* HeapTupleHeader ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int GetMultiXactIdMembers (void*,TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ HEAP_LOCKED_UPGRADED (int) ; 
 int HEAP_MOVED ; 
 int /*<<< orphan*/  HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 void* HeapTupleHeaderGetRawXmax (TYPE_2__*) ; 
 void* HeapTupleHeaderGetXmin (TYPE_2__*) ; 
 void* HeapTupleHeaderGetXvac (TYPE_2__*) ; 
 int /*<<< orphan*/  MultiXactIdIsValid (void*) ; 
 scalar_t__ MultiXactIdPrecedes (void*,void*) ; 
 scalar_t__ TransactionIdIsNormal (void*) ; 
 scalar_t__ TransactionIdPrecedes (void*,void*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

bool
heap_tuple_needs_freeze(HeapTupleHeader tuple, TransactionId cutoff_xid,
						MultiXactId cutoff_multi, Buffer buf)
{
	TransactionId xid;

	xid = HeapTupleHeaderGetXmin(tuple);
	if (TransactionIdIsNormal(xid) &&
		TransactionIdPrecedes(xid, cutoff_xid))
		return true;

	/*
	 * The considerations for multixacts are complicated; look at
	 * heap_prepare_freeze_tuple for justifications.  This routine had better
	 * be in sync with that one!
	 */
	if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
	{
		MultiXactId multi;

		multi = HeapTupleHeaderGetRawXmax(tuple);
		if (!MultiXactIdIsValid(multi))
		{
			/* no xmax set, ignore */
			;
		}
		else if (HEAP_LOCKED_UPGRADED(tuple->t_infomask))
			return true;
		else if (MultiXactIdPrecedes(multi, cutoff_multi))
			return true;
		else
		{
			MultiXactMember *members;
			int			nmembers;
			int			i;

			/* need to check whether any member of the mxact is too old */

			nmembers = GetMultiXactIdMembers(multi, &members, false,
											 HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask));

			for (i = 0; i < nmembers; i++)
			{
				if (TransactionIdPrecedes(members[i].xid, cutoff_xid))
				{
					pfree(members);
					return true;
				}
			}
			if (nmembers > 0)
				pfree(members);
		}
	}
	else
	{
		xid = HeapTupleHeaderGetRawXmax(tuple);
		if (TransactionIdIsNormal(xid) &&
			TransactionIdPrecedes(xid, cutoff_xid))
			return true;
	}

	if (tuple->t_infomask & HEAP_MOVED)
	{
		xid = HeapTupleHeaderGetXvac(tuple);
		if (TransactionIdIsNormal(xid) &&
			TransactionIdPrecedes(xid, cutoff_xid))
			return true;
	}

	return false;
}