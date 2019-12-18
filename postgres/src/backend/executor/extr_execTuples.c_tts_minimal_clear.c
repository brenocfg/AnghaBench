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
struct TYPE_5__ {int /*<<< orphan*/  tts_tid; int /*<<< orphan*/  tts_flags; scalar_t__ tts_nvalid; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/ * mintuple; scalar_t__ off; } ;
typedef  TYPE_2__ MinimalTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 
 int /*<<< orphan*/  TTS_FLAG_SHOULDFREE ; 
 scalar_t__ TTS_SHOULDFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free_minimal_tuple (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tts_minimal_clear(TupleTableSlot *slot)
{
	MinimalTupleTableSlot *mslot = (MinimalTupleTableSlot *) slot;

	if (TTS_SHOULDFREE(slot))
	{
		heap_free_minimal_tuple(mslot->mintuple);
		slot->tts_flags &= ~TTS_FLAG_SHOULDFREE;
	}

	slot->tts_nvalid = 0;
	slot->tts_flags |= TTS_FLAG_EMPTY;
	ItemPointerSetInvalid(&slot->tts_tid);
	mslot->off = 0;
	mslot->mintuple = NULL;
}