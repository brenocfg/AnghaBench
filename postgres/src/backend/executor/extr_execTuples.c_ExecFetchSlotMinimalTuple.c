#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* tts_ops; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_7__ {int /*<<< orphan*/  (* copy_minimal_tuple ) (TYPE_2__*) ;int /*<<< orphan*/  (* get_minimal_tuple ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  MinimalTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_EMPTY (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

MinimalTuple
ExecFetchSlotMinimalTuple(TupleTableSlot *slot,
						  bool *shouldFree)
{
	/*
	 * sanity checks
	 */
	Assert(slot != NULL);
	Assert(!TTS_EMPTY(slot));

	if (slot->tts_ops->get_minimal_tuple)
	{
		if (shouldFree)
			*shouldFree = false;
		return slot->tts_ops->get_minimal_tuple(slot);
	}
	else
	{
		if (shouldFree)
			*shouldFree = true;
		return slot->tts_ops->copy_minimal_tuple(slot);
	}
}