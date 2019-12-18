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
struct TYPE_11__ {scalar_t__ tts_ops; int /*<<< orphan*/  tts_flags; int /*<<< orphan*/  tts_mcxt; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_10__ {int /*<<< orphan*/  tupdata; int /*<<< orphan*/ * tuple; } ;
struct TYPE_12__ {TYPE_1__ base; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTupleData ;
typedef  TYPE_3__ BufferHeapTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_2__*) ; 
 int /*<<< orphan*/ * ExecCopySlotHeapTuple (TYPE_2__*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 
 int /*<<< orphan*/  TTS_FLAG_SHOULDFREE ; 
 scalar_t__ TTS_SHOULDFREE (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tts_buffer_heap_store_tuple (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tts_buffer_heap_copyslot(TupleTableSlot *dstslot, TupleTableSlot *srcslot)
{
	BufferHeapTupleTableSlot *bsrcslot = (BufferHeapTupleTableSlot *) srcslot;
	BufferHeapTupleTableSlot *bdstslot = (BufferHeapTupleTableSlot *) dstslot;

	/*
	 * If the source slot is of a different kind, or is a buffer slot that has
	 * been materialized / is virtual, make a new copy of the tuple. Otherwise
	 * make a new reference to the in-buffer tuple.
	 */
	if (dstslot->tts_ops != srcslot->tts_ops ||
		TTS_SHOULDFREE(srcslot) ||
		!bsrcslot->base.tuple)
	{
		MemoryContext oldContext;

		ExecClearTuple(dstslot);
		dstslot->tts_flags &= ~TTS_FLAG_EMPTY;
		oldContext = MemoryContextSwitchTo(dstslot->tts_mcxt);
		bdstslot->base.tuple = ExecCopySlotHeapTuple(srcslot);
		dstslot->tts_flags |= TTS_FLAG_SHOULDFREE;
		MemoryContextSwitchTo(oldContext);
	}
	else
	{
		Assert(BufferIsValid(bsrcslot->buffer));

		tts_buffer_heap_store_tuple(dstslot, bsrcslot->base.tuple,
									bsrcslot->buffer, false);

		/*
		 * The HeapTupleData portion of the source tuple might be shorter
		 * lived than the destination slot. Therefore copy the HeapTuple into
		 * our slot's tupdata, which is guaranteed to live long enough (but
		 * will still point into the buffer).
		 */
		memcpy(&bdstslot->base.tupdata, bdstslot->base.tuple, sizeof(HeapTupleData));
		bdstslot->base.tuple = &bdstslot->base.tupdata;
	}
}