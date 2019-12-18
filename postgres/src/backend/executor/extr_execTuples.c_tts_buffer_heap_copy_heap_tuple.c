#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  tuple; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ BufferHeapTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tts_buffer_heap_materialize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HeapTuple
tts_buffer_heap_copy_heap_tuple(TupleTableSlot *slot)
{
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;

	Assert(!TTS_EMPTY(slot));

	if (!bslot->base.tuple)
		tts_buffer_heap_materialize(slot);

	return heap_copytuple(bslot->base.tuple);
}