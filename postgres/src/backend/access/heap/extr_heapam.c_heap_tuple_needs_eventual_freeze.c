#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* TransactionId ;
struct TYPE_6__ {int t_infomask; } ;
typedef  void* MultiXactId ;
typedef  TYPE_1__* HeapTupleHeader ;

/* Variables and functions */
 int HEAP_MOVED ; 
 int HEAP_XMAX_IS_MULTI ; 
 void* HeapTupleHeaderGetRawXmax (TYPE_1__*) ; 
 void* HeapTupleHeaderGetXmin (TYPE_1__*) ; 
 void* HeapTupleHeaderGetXvac (TYPE_1__*) ; 
 scalar_t__ MultiXactIdIsValid (void*) ; 
 scalar_t__ TransactionIdIsNormal (void*) ; 

bool
heap_tuple_needs_eventual_freeze(HeapTupleHeader tuple)
{
	TransactionId xid;

	/*
	 * If xmin is a normal transaction ID, this tuple is definitely not
	 * frozen.
	 */
	xid = HeapTupleHeaderGetXmin(tuple);
	if (TransactionIdIsNormal(xid))
		return true;

	/*
	 * If xmax is a valid xact or multixact, this tuple is also not frozen.
	 */
	if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
	{
		MultiXactId multi;

		multi = HeapTupleHeaderGetRawXmax(tuple);
		if (MultiXactIdIsValid(multi))
			return true;
	}
	else
	{
		xid = HeapTupleHeaderGetRawXmax(tuple);
		if (TransactionIdIsNormal(xid))
			return true;
	}

	if (tuple->t_infomask & HEAP_MOVED)
	{
		xid = HeapTupleHeaderGetXvac(tuple);
		if (TransactionIdIsNormal(xid))
			return true;
	}

	return false;
}