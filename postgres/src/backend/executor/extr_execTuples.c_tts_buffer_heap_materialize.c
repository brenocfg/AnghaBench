#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tts_flags; int /*<<< orphan*/  tts_isnull; int /*<<< orphan*/  tts_values; int /*<<< orphan*/  tts_tupleDescriptor; scalar_t__ tts_nvalid; int /*<<< orphan*/  tts_mcxt; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_7__ {scalar_t__ tuple; scalar_t__ off; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ BufferHeapTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_EMPTY (TYPE_2__*) ; 
 int /*<<< orphan*/  TTS_FLAG_SHOULDFREE ; 
 scalar_t__ TTS_SHOULDFREE (TYPE_2__*) ; 
 scalar_t__ heap_copytuple (scalar_t__) ; 
 scalar_t__ heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tts_buffer_heap_materialize(TupleTableSlot *slot)
{
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;
	MemoryContext oldContext;

	Assert(!TTS_EMPTY(slot));

	/* If slot has its tuple already materialized, nothing to do. */
	if (TTS_SHOULDFREE(slot))
		return;

	oldContext = MemoryContextSwitchTo(slot->tts_mcxt);

	/*
	 * Have to deform from scratch, otherwise tts_values[] entries could point
	 * into the non-materialized tuple (which might be gone when accessed).
	 */
	bslot->base.off = 0;
	slot->tts_nvalid = 0;

	if (!bslot->base.tuple)
	{
		/*
		 * Normally BufferHeapTupleTableSlot should have a tuple + buffer
		 * associated with it, unless it's materialized (which would've
		 * returned above). But when it's useful to allow storing virtual
		 * tuples in a buffer slot, which then also needs to be
		 * materializable.
		 */
		bslot->base.tuple = heap_form_tuple(slot->tts_tupleDescriptor,
											slot->tts_values,
											slot->tts_isnull);
	}
	else
	{
		bslot->base.tuple = heap_copytuple(bslot->base.tuple);

		/*
		 * A heap tuple stored in a BufferHeapTupleTableSlot should have a
		 * buffer associated with it, unless it's materialized or virtual.
		 */
		if (likely(BufferIsValid(bslot->buffer)))
			ReleaseBuffer(bslot->buffer);
		bslot->buffer = InvalidBuffer;
	}

	/*
	 * We don't set TTS_FLAG_SHOULDFREE until after releasing the buffer, if
	 * any.  This avoids having a transient state that would fall foul of our
	 * assertions that a slot with TTS_FLAG_SHOULDFREE doesn't own a buffer.
	 * In the unlikely event that ReleaseBuffer() above errors out, we'd
	 * effectively leak the copied tuple, but that seems fairly harmless.
	 */
	slot->tts_flags |= TTS_FLAG_SHOULDFREE;

	MemoryContextSwitchTo(oldContext);
}