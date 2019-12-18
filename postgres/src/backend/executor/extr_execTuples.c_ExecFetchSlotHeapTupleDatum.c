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
struct TYPE_4__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ExecFetchSlotHeapTuple (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  heap_copy_tuple_as_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

Datum
ExecFetchSlotHeapTupleDatum(TupleTableSlot *slot)
{
	HeapTuple	tup;
	TupleDesc	tupdesc;
	bool		shouldFree;
	Datum		ret;

	/* Fetch slot's contents in regular-physical-tuple form */
	tup = ExecFetchSlotHeapTuple(slot, false, &shouldFree);
	tupdesc = slot->tts_tupleDescriptor;

	/* Convert to Datum form */
	ret = heap_copy_tuple_as_datum(tup, tupdesc);

	if (shouldFree)
		pfree(tup);

	return ret;
}