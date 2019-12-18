#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_2__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ HeapTupleTableSlot ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tts_heap_materialize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HeapTuple
tts_heap_get_heap_tuple(TupleTableSlot *slot)
{
	HeapTupleTableSlot *hslot = (HeapTupleTableSlot *) slot;

	Assert(!TTS_EMPTY(slot));
	if (!hslot->tuple)
		tts_heap_materialize(slot);

	return hslot->tuple;
}