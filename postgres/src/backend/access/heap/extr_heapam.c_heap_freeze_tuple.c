#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xl_heap_freeze_tuple ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;

/* Variables and functions */
 int /*<<< orphan*/  heap_execute_freeze_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int heap_prepare_freeze_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

bool
heap_freeze_tuple(HeapTupleHeader tuple,
				  TransactionId relfrozenxid, TransactionId relminmxid,
				  TransactionId cutoff_xid, TransactionId cutoff_multi)
{
	xl_heap_freeze_tuple frz;
	bool		do_freeze;
	bool		tuple_totally_frozen;

	do_freeze = heap_prepare_freeze_tuple(tuple,
										  relfrozenxid, relminmxid,
										  cutoff_xid, cutoff_multi,
										  &frz, &tuple_totally_frozen);

	/*
	 * Note that because this is not a WAL-logged operation, we don't need to
	 * fill in the offset in the freeze record.
	 */

	if (do_freeze)
		heap_execute_freeze_tuple(tuple, &frz);
	return do_freeze;
}