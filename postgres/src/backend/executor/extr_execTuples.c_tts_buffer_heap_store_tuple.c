#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tts_tid; scalar_t__ tts_nvalid; int /*<<< orphan*/  tts_flags; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_9__ {scalar_t__ off; TYPE_3__* tuple; } ;
struct TYPE_12__ {scalar_t__ buffer; TYPE_1__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__ BufferHeapTupleTableSlot ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BufferIsValid (scalar_t__) ; 
 int /*<<< orphan*/  IncrBufferRefCount (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 
 int /*<<< orphan*/  TTS_FLAG_SHOULDFREE ; 
 scalar_t__ TTS_SHOULDFREE (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 

__attribute__((used)) static inline void
tts_buffer_heap_store_tuple(TupleTableSlot *slot, HeapTuple tuple,
							Buffer buffer, bool transfer_pin)
{
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;

	if (TTS_SHOULDFREE(slot))
	{
		/* materialized slot shouldn't have a buffer to release */
		Assert(!BufferIsValid(bslot->buffer));

		heap_freetuple(bslot->base.tuple);
		slot->tts_flags &= ~TTS_FLAG_SHOULDFREE;
	}

	slot->tts_flags &= ~TTS_FLAG_EMPTY;
	slot->tts_nvalid = 0;
	bslot->base.tuple = tuple;
	bslot->base.off = 0;
	slot->tts_tid = tuple->t_self;

	/*
	 * If tuple is on a disk page, keep the page pinned as long as we hold a
	 * pointer into it.  We assume the caller already has such a pin.  If
	 * transfer_pin is true, we'll transfer that pin to this slot, if not
	 * we'll pin it again ourselves.
	 *
	 * This is coded to optimize the case where the slot previously held a
	 * tuple on the same disk page: in that case releasing and re-acquiring
	 * the pin is a waste of cycles.  This is a common situation during
	 * seqscans, so it's worth troubling over.
	 */
	if (bslot->buffer != buffer)
	{
		if (BufferIsValid(bslot->buffer))
			ReleaseBuffer(bslot->buffer);

		bslot->buffer = buffer;

		if (!transfer_pin && BufferIsValid(buffer))
			IncrBufferRefCount(buffer);
	}
	else if (transfer_pin && BufferIsValid(buffer))
	{
		/*
		 * In transfer_pin mode the caller won't know about the same-page
		 * optimization, so we gotta release its pin.
		 */
		ReleaseBuffer(buffer);
	}
}