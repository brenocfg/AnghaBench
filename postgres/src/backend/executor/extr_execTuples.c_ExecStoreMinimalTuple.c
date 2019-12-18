#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  int /*<<< orphan*/ * MinimalTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  TTS_IS_MINIMALTUPLE (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tts_minimal_store_tuple (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

TupleTableSlot *
ExecStoreMinimalTuple(MinimalTuple mtup,
					  TupleTableSlot *slot,
					  bool shouldFree)
{
	/*
	 * sanity checks
	 */
	Assert(mtup != NULL);
	Assert(slot != NULL);
	Assert(slot->tts_tupleDescriptor != NULL);

	if (unlikely(!TTS_IS_MINIMALTUPLE(slot)))
		elog(ERROR, "trying to store a minimal tuple into wrong type of slot");
	tts_minimal_store_tuple(slot, mtup, shouldFree);

	return slot;
}