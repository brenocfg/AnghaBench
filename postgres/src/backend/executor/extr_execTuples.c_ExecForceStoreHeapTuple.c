#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tts_isnull; int /*<<< orphan*/  tts_values; int /*<<< orphan*/  tts_tupleDescriptor; int /*<<< orphan*/  tts_flags; int /*<<< orphan*/  tts_mcxt; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_11__ {int /*<<< orphan*/  tuple; } ;
struct TYPE_13__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ BufferHeapTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecStoreHeapTuple (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 
 int /*<<< orphan*/  TTS_FLAG_SHOULDFREE ; 
 scalar_t__ TTS_IS_BUFFERTUPLE (TYPE_2__*) ; 
 scalar_t__ TTS_IS_HEAPTUPLE (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_deform_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 

void
ExecForceStoreHeapTuple(HeapTuple tuple,
						TupleTableSlot *slot,
						bool shouldFree)
{
	if (TTS_IS_HEAPTUPLE(slot))
	{
		ExecStoreHeapTuple(tuple, slot, shouldFree);
	}
	else if (TTS_IS_BUFFERTUPLE(slot))
	{
		MemoryContext oldContext;
		BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;

		ExecClearTuple(slot);
		slot->tts_flags &= ~TTS_FLAG_EMPTY;
		oldContext = MemoryContextSwitchTo(slot->tts_mcxt);
		bslot->base.tuple = heap_copytuple(tuple);
		slot->tts_flags |= TTS_FLAG_SHOULDFREE;
		MemoryContextSwitchTo(oldContext);

		if (shouldFree)
			pfree(tuple);
	}
	else
	{
		ExecClearTuple(slot);
		heap_deform_tuple(tuple, slot->tts_tupleDescriptor,
						  slot->tts_values, slot->tts_isnull);
		ExecStoreVirtualTuple(slot);

		if (shouldFree)
		{
			ExecMaterializeSlot(slot);
			pfree(tuple);
		}
	}
}