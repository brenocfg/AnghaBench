#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tts_tableOid; } ;
typedef  TYPE_2__ TupleTableSlot ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_9__ {TYPE_5__ tupdata; } ;
struct TYPE_11__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_3__ BufferHeapTupleTableSlot ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecStorePinnedBufferHeapTuple (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_IS_BUFFERTUPLE (TYPE_2__*) ; 
 scalar_t__ heap_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
heapam_fetch_row_version(Relation relation,
						 ItemPointer tid,
						 Snapshot snapshot,
						 TupleTableSlot *slot)
{
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;
	Buffer		buffer;

	Assert(TTS_IS_BUFFERTUPLE(slot));

	bslot->base.tupdata.t_self = *tid;
	if (heap_fetch(relation, snapshot, &bslot->base.tupdata, &buffer))
	{
		/* store in slot, transferring existing pin */
		ExecStorePinnedBufferHeapTuple(&bslot->base.tupdata, slot, buffer);
		slot->tts_tableOid = RelationGetRelid(relation);

		return true;
	}

	return false;
}