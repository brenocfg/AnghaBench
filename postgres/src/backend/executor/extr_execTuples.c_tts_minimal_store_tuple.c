#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  tts_flags; scalar_t__ tts_nvalid; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_13__ {int t_len; } ;
struct TYPE_10__ {char* t_len; scalar_t__ t_data; } ;
struct TYPE_12__ {TYPE_1__ minhdr; TYPE_1__* tuple; TYPE_4__* mintuple; scalar_t__ off; } ;
typedef  TYPE_3__ MinimalTupleTableSlot ;
typedef  TYPE_4__* MinimalTuple ;
typedef  scalar_t__ HeapTupleHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* MINIMAL_TUPLE_OFFSET ; 
 int TTS_EMPTY (TYPE_2__*) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 
 int /*<<< orphan*/  TTS_FLAG_SHOULDFREE ; 
 int /*<<< orphan*/  TTS_SHOULDFREE (TYPE_2__*) ; 
 int /*<<< orphan*/  tts_minimal_clear (TYPE_2__*) ; 

__attribute__((used)) static void
tts_minimal_store_tuple(TupleTableSlot *slot, MinimalTuple mtup, bool shouldFree)
{
	MinimalTupleTableSlot *mslot = (MinimalTupleTableSlot *) slot;

	tts_minimal_clear(slot);

	Assert(!TTS_SHOULDFREE(slot));
	Assert(TTS_EMPTY(slot));

	slot->tts_flags &= ~TTS_FLAG_EMPTY;
	slot->tts_nvalid = 0;
	mslot->off = 0;

	mslot->mintuple = mtup;
	Assert(mslot->tuple == &mslot->minhdr);
	mslot->minhdr.t_len = mtup->t_len + MINIMAL_TUPLE_OFFSET;
	mslot->minhdr.t_data = (HeapTupleHeader) ((char *) mtup - MINIMAL_TUPLE_OFFSET);
	/* no need to set t_self or t_tableOid since we won't allow access */

	if (shouldFree)
		slot->tts_flags |= TTS_FLAG_SHOULDFREE;
}