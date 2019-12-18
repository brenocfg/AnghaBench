#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct IndexFetchTableData {int /*<<< orphan*/  rel; } ;
struct TYPE_13__ {int /*<<< orphan*/  tts_tableOid; } ;
typedef  TYPE_3__ TupleTableSlot ;
struct TYPE_16__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_12__ {TYPE_7__ tupdata; } ;
struct TYPE_15__ {TYPE_2__ base; } ;
struct TYPE_11__ {int /*<<< orphan*/  rel; } ;
struct TYPE_14__ {scalar_t__ xs_cbuf; TYPE_1__ xs_base; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_4__ IndexFetchHeapData ;
typedef  TYPE_5__ BufferHeapTupleTableSlot ;
typedef  scalar_t__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  ExecStoreBufferHeapTuple (TYPE_7__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  IsMVCCSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 scalar_t__ ReleaseAndReadBuffer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_IS_BUFFERTUPLE (TYPE_3__*) ; 
 int heap_hot_search_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_7__*,int*,int) ; 
 int /*<<< orphan*/  heap_page_prune_opt (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
heapam_index_fetch_tuple(struct IndexFetchTableData *scan,
						 ItemPointer tid,
						 Snapshot snapshot,
						 TupleTableSlot *slot,
						 bool *call_again, bool *all_dead)
{
	IndexFetchHeapData *hscan = (IndexFetchHeapData *) scan;
	BufferHeapTupleTableSlot *bslot = (BufferHeapTupleTableSlot *) slot;
	bool		got_heap_tuple;

	Assert(TTS_IS_BUFFERTUPLE(slot));

	/* We can skip the buffer-switching logic if we're in mid-HOT chain. */
	if (!*call_again)
	{
		/* Switch to correct buffer if we don't have it already */
		Buffer		prev_buf = hscan->xs_cbuf;

		hscan->xs_cbuf = ReleaseAndReadBuffer(hscan->xs_cbuf,
											  hscan->xs_base.rel,
											  ItemPointerGetBlockNumber(tid));

		/*
		 * Prune page, but only if we weren't already on this page
		 */
		if (prev_buf != hscan->xs_cbuf)
			heap_page_prune_opt(hscan->xs_base.rel, hscan->xs_cbuf);
	}

	/* Obtain share-lock on the buffer so we can examine visibility */
	LockBuffer(hscan->xs_cbuf, BUFFER_LOCK_SHARE);
	got_heap_tuple = heap_hot_search_buffer(tid,
											hscan->xs_base.rel,
											hscan->xs_cbuf,
											snapshot,
											&bslot->base.tupdata,
											all_dead,
											!*call_again);
	bslot->base.tupdata.t_self = *tid;
	LockBuffer(hscan->xs_cbuf, BUFFER_LOCK_UNLOCK);

	if (got_heap_tuple)
	{
		/*
		 * Only in a non-MVCC snapshot can more than one member of the HOT
		 * chain be visible.
		 */
		*call_again = !IsMVCCSnapshot(snapshot);

		slot->tts_tableOid = RelationGetRelid(scan->rel);
		ExecStoreBufferHeapTuple(&bslot->base.tupdata, slot, hscan->xs_cbuf);
	}
	else
	{
		/* We've reached the end of the HOT chain. */
		*call_again = false;
	}

	return got_heap_tuple;
}