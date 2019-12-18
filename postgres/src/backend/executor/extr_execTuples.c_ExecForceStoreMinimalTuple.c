#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  tts_isnull; int /*<<< orphan*/  tts_values; int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_16__ {char* t_len; scalar_t__ t_data; } ;
struct TYPE_15__ {int t_len; } ;
typedef  TYPE_2__* MinimalTuple ;
typedef  scalar_t__ HeapTupleHeader ;
typedef  TYPE_3__ HeapTupleData ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_1__*) ; 
 char* MINIMAL_TUPLE_OFFSET ; 
 scalar_t__ TTS_IS_MINIMALTUPLE (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_deform_tuple (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 int /*<<< orphan*/  tts_minimal_store_tuple (TYPE_1__*,TYPE_2__*,int) ; 

void
ExecForceStoreMinimalTuple(MinimalTuple mtup,
						   TupleTableSlot *slot,
						   bool shouldFree)
{
	if (TTS_IS_MINIMALTUPLE(slot))
	{
		tts_minimal_store_tuple(slot, mtup, shouldFree);
	}
	else
	{
		HeapTupleData htup;

		ExecClearTuple(slot);

		htup.t_len = mtup->t_len + MINIMAL_TUPLE_OFFSET;
		htup.t_data = (HeapTupleHeader) ((char *) mtup - MINIMAL_TUPLE_OFFSET);
		heap_deform_tuple(&htup, slot->tts_tupleDescriptor,
						  slot->tts_values, slot->tts_isnull);
		ExecStoreVirtualTuple(slot);

		if (shouldFree)
		{
			ExecMaterializeSlot(slot);
			pfree(mtup);
		}
	}
}