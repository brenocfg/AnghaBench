#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TransactionId ;
struct TYPE_8__ {int t_infomask; } ;
typedef  TYPE_1__* HeapTupleHeader ;

/* Variables and functions */
 int HEAP_MOVED ; 
 scalar_t__ HeapTupleHeaderGetUpdateXid (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderGetXmin (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderGetXvac (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderXminCommitted (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderXminInvalid (TYPE_1__*) ; 
 scalar_t__ TransactionIdDidCommit (scalar_t__) ; 
 scalar_t__ TransactionIdFollows (scalar_t__,scalar_t__) ; 
 scalar_t__ TransactionIdPrecedes (scalar_t__,scalar_t__) ; 

void
HeapTupleHeaderAdvanceLatestRemovedXid(HeapTupleHeader tuple,
									   TransactionId *latestRemovedXid)
{
	TransactionId xmin = HeapTupleHeaderGetXmin(tuple);
	TransactionId xmax = HeapTupleHeaderGetUpdateXid(tuple);
	TransactionId xvac = HeapTupleHeaderGetXvac(tuple);

	if (tuple->t_infomask & HEAP_MOVED)
	{
		if (TransactionIdPrecedes(*latestRemovedXid, xvac))
			*latestRemovedXid = xvac;
	}

	/*
	 * Ignore tuples inserted by an aborted transaction or if the tuple was
	 * updated/deleted by the inserting transaction.
	 *
	 * Look for a committed hint bit, or if no xmin bit is set, check clog.
	 * This needs to work on both master and standby, where it is used to
	 * assess btree delete records.
	 */
	if (HeapTupleHeaderXminCommitted(tuple) ||
		(!HeapTupleHeaderXminInvalid(tuple) && TransactionIdDidCommit(xmin)))
	{
		if (xmax != xmin &&
			TransactionIdFollows(xmax, *latestRemovedXid))
			*latestRemovedXid = xmax;
	}

	/* *latestRemovedXid may still be invalid at end */
}