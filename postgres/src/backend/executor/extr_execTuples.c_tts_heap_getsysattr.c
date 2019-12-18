#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ HeapTupleTableSlot ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_EMPTY (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_getsysattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static Datum
tts_heap_getsysattr(TupleTableSlot *slot, int attnum, bool *isnull)
{
	HeapTupleTableSlot *hslot = (HeapTupleTableSlot *) slot;

	Assert(!TTS_EMPTY(slot));

	return heap_getsysattr(hslot->tuple, attnum,
						   slot->tts_tupleDescriptor, isnull);
}