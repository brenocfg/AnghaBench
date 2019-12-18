#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* tts_tupleDescriptor; int /*<<< orphan*/  tts_nvalid; int /*<<< orphan*/  tts_flags; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/  natts; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_EMPTY (TYPE_2__*) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 

TupleTableSlot *
ExecStoreVirtualTuple(TupleTableSlot *slot)
{
	/*
	 * sanity checks
	 */
	Assert(slot != NULL);
	Assert(slot->tts_tupleDescriptor != NULL);
	Assert(TTS_EMPTY(slot));

	slot->tts_flags &= ~TTS_FLAG_EMPTY;
	slot->tts_nvalid = slot->tts_tupleDescriptor->natts;

	return slot;
}