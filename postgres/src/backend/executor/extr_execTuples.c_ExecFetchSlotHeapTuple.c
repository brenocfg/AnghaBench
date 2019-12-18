#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* tts_ops; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_heap_tuple ) (TYPE_2__*) ;int /*<<< orphan*/  (* copy_heap_tuple ) (TYPE_2__*) ;int /*<<< orphan*/  (* materialize ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_EMPTY (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

HeapTuple
ExecFetchSlotHeapTuple(TupleTableSlot *slot, bool materialize, bool *shouldFree)
{
	/*
	 * sanity checks
	 */
	Assert(slot != NULL);
	Assert(!TTS_EMPTY(slot));

	/* Materialize the tuple so that the slot "owns" it, if requested. */
	if (materialize)
		slot->tts_ops->materialize(slot);

	if (slot->tts_ops->get_heap_tuple == NULL)
	{
		if (shouldFree)
			*shouldFree = true;
		return slot->tts_ops->copy_heap_tuple(slot);
	}
	else
	{
		if (shouldFree)
			*shouldFree = false;
		return slot->tts_ops->get_heap_tuple(slot);
	}
}