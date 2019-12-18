#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tts_tableOid; int /*<<< orphan*/ * tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_10__ {int /*<<< orphan*/  t_tableOid; } ;
typedef  TYPE_2__* HeapTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  TTS_IS_BUFFERTUPLE (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tts_buffer_heap_store_tuple (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

TupleTableSlot *
ExecStorePinnedBufferHeapTuple(HeapTuple tuple,
							   TupleTableSlot *slot,
							   Buffer buffer)
{
	/*
	 * sanity checks
	 */
	Assert(tuple != NULL);
	Assert(slot != NULL);
	Assert(slot->tts_tupleDescriptor != NULL);
	Assert(BufferIsValid(buffer));

	if (unlikely(!TTS_IS_BUFFERTUPLE(slot)))
		elog(ERROR, "trying to store an on-disk heap tuple into wrong type of slot");
	tts_buffer_heap_store_tuple(slot, tuple, buffer, true);

	slot->tts_tableOid = tuple->t_tableOid;

	return slot;
}