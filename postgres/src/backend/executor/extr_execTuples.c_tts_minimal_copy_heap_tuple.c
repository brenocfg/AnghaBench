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
struct TYPE_2__ {int /*<<< orphan*/  mintuple; } ;
typedef  TYPE_1__ MinimalTupleTableSlot ;
typedef  int /*<<< orphan*/  HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  heap_tuple_from_minimal_tuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tts_minimal_materialize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HeapTuple
tts_minimal_copy_heap_tuple(TupleTableSlot *slot)
{
	MinimalTupleTableSlot *mslot = (MinimalTupleTableSlot *) slot;

	if (!mslot->mintuple)
		tts_minimal_materialize(slot);

	return heap_tuple_from_minimal_tuple(mslot->mintuple);
}