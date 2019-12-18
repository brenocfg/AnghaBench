#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tts_nvalid; int /*<<< orphan*/  tts_flags; int /*<<< orphan*/ * tts_isnull; int /*<<< orphan*/ * tts_values; TYPE_2__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_9__ {scalar_t__ natts; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  TTS_FLAG_EMPTY ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 
 int /*<<< orphan*/  tts_virtual_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  tts_virtual_materialize (TYPE_1__*) ; 

__attribute__((used)) static void
tts_virtual_copyslot(TupleTableSlot *dstslot, TupleTableSlot *srcslot)
{
	TupleDesc	srcdesc = srcslot->tts_tupleDescriptor;

	Assert(srcdesc->natts <= dstslot->tts_tupleDescriptor->natts);

	tts_virtual_clear(dstslot);

	slot_getallattrs(srcslot);

	for (int natt = 0; natt < srcdesc->natts; natt++)
	{
		dstslot->tts_values[natt] = srcslot->tts_values[natt];
		dstslot->tts_isnull[natt] = srcslot->tts_isnull[natt];
	}

	dstslot->tts_nvalid = srcdesc->natts;
	dstslot->tts_flags &= ~TTS_FLAG_EMPTY;

	/* make sure storage doesn't depend on external memory */
	tts_virtual_materialize(dstslot);
}