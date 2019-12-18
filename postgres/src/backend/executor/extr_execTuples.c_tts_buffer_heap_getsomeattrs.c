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
struct TYPE_3__ {int /*<<< orphan*/  off; int /*<<< orphan*/  tuple; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
typedef  TYPE_2__ BufferHeapTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_deform_heap_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
tts_buffer_heap_getsomeattrs(TupleTableSlot *slot, int natts)
{
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;

	Assert(!TTS_EMPTY(slot));

	slot_deform_heap_tuple(slot, bslot->base.tuple, &bslot->base.off, natts);
}