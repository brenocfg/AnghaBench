#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {scalar_t__ t_tableOid; int /*<<< orphan*/  t_self; TYPE_1__* t_data; } ;
struct TYPE_7__ {int t_infomask; } ;
typedef  TYPE_1__* HeapTupleHeader ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int HEAP_XMAX_COMMITTED ; 
 int HEAP_XMAX_INVALID ; 
 scalar_t__ HEAP_XMAX_IS_LOCKED_ONLY (int) ; 
 int HEAP_XMAX_IS_MULTI ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmax (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderXminCommitted (TYPE_1__*) ; 
 scalar_t__ HeapTupleHeaderXminInvalid (TYPE_1__*) ; 
 scalar_t__ InvalidOid ; 
 int ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
HeapTupleIsSurelyDead(HeapTuple htup, TransactionId OldestXmin)
{
	HeapTupleHeader tuple = htup->t_data;

	Assert(ItemPointerIsValid(&htup->t_self));
	Assert(htup->t_tableOid != InvalidOid);

	/*
	 * If the inserting transaction is marked invalid, then it aborted, and
	 * the tuple is definitely dead.  If it's marked neither committed nor
	 * invalid, then we assume it's still alive (since the presumption is that
	 * all relevant hint bits were just set moments ago).
	 */
	if (!HeapTupleHeaderXminCommitted(tuple))
		return HeapTupleHeaderXminInvalid(tuple) ? true : false;

	/*
	 * If the inserting transaction committed, but any deleting transaction
	 * aborted, the tuple is still alive.
	 */
	if (tuple->t_infomask & HEAP_XMAX_INVALID)
		return false;

	/*
	 * If the XMAX is just a lock, the tuple is still alive.
	 */
	if (HEAP_XMAX_IS_LOCKED_ONLY(tuple->t_infomask))
		return false;

	/*
	 * If the Xmax is a MultiXact, it might be dead or alive, but we cannot
	 * know without checking pg_multixact.
	 */
	if (tuple->t_infomask & HEAP_XMAX_IS_MULTI)
		return false;

	/* If deleter isn't known to have committed, assume it's still running. */
	if (!(tuple->t_infomask & HEAP_XMAX_COMMITTED))
		return false;

	/* Deleter committed, so tuple is dead if the XID is old enough. */
	return TransactionIdPrecedes(HeapTupleHeaderGetRawXmax(tuple), OldestXmin);
}