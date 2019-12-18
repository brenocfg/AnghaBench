#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tts_isnull; int /*<<< orphan*/  tts_values; int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_12__ {TYPE_2__* t_data; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_ctid; } ;
typedef  TYPE_2__* HeapTupleHeader ;
typedef  TYPE_3__ HeapTupleData ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 TYPE_2__* DatumGetHeapTupleHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ExecStoreHeapTupleDatum(Datum data, TupleTableSlot *slot)
{
	HeapTupleData tuple = {0};
	HeapTupleHeader td;

	td = DatumGetHeapTupleHeader(data);

	tuple.t_len = HeapTupleHeaderGetDatumLength(td);
	tuple.t_self = td->t_ctid;
	tuple.t_data = td;

	ExecClearTuple(slot);

	heap_deform_tuple(&tuple, slot->tts_tupleDescriptor,
					  slot->tts_values, slot->tts_isnull);
	ExecStoreVirtualTuple(slot);
}