#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int flags; } ;
typedef  TYPE_5__ xl_heap_delete ;
struct TYPE_22__ {int /*<<< orphan*/  origptr; int /*<<< orphan*/ * record; } ;
typedef  TYPE_6__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  XLogReaderState ;
struct TYPE_25__ {int /*<<< orphan*/  reorder; TYPE_2__* slot; } ;
struct TYPE_24__ {scalar_t__ dbNode; } ;
struct TYPE_19__ {int clear_toast_afterwards; int /*<<< orphan*/  oldtuple; int /*<<< orphan*/  relnode; } ;
struct TYPE_20__ {TYPE_3__ tp; } ;
struct TYPE_23__ {TYPE_4__ data; int /*<<< orphan*/  origin_id; int /*<<< orphan*/  action; } ;
struct TYPE_17__ {scalar_t__ database; } ;
struct TYPE_18__ {TYPE_1__ data; } ;
typedef  scalar_t__ Size ;
typedef  TYPE_7__ ReorderBufferChange ;
typedef  TYPE_8__ RelFileNode ;
typedef  TYPE_9__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DecodeXLogTuple (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FilterByOrigin (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REORDER_BUFFER_CHANGE_DELETE ; 
 TYPE_7__* ReorderBufferGetChange (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferGetTupleBuf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReorderBufferQueueChange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ SizeOfHeapDelete ; 
 scalar_t__ SizeOfHeapHeader ; 
 int XLH_DELETE_CONTAINS_OLD ; 
 int XLH_DELETE_IS_SUPER ; 
 int /*<<< orphan*/  XLogRecGetBlockTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 scalar_t__ XLogRecGetDataLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetOrigin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetXid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_8__*,int) ; 

__attribute__((used)) static void
DecodeDelete(LogicalDecodingContext *ctx, XLogRecordBuffer *buf)
{
	XLogReaderState *r = buf->record;
	xl_heap_delete *xlrec;
	ReorderBufferChange *change;
	RelFileNode target_node;

	xlrec = (xl_heap_delete *) XLogRecGetData(r);

	/* only interested in our database */
	XLogRecGetBlockTag(r, 0, &target_node, NULL, NULL);
	if (target_node.dbNode != ctx->slot->data.database)
		return;

	/*
	 * Super deletions are irrelevant for logical decoding, it's driven by the
	 * confirmation records.
	 */
	if (xlrec->flags & XLH_DELETE_IS_SUPER)
		return;

	/* output plugin doesn't look for this origin, no need to queue */
	if (FilterByOrigin(ctx, XLogRecGetOrigin(r)))
		return;

	change = ReorderBufferGetChange(ctx->reorder);
	change->action = REORDER_BUFFER_CHANGE_DELETE;
	change->origin_id = XLogRecGetOrigin(r);

	memcpy(&change->data.tp.relnode, &target_node, sizeof(RelFileNode));

	/* old primary key stored */
	if (xlrec->flags & XLH_DELETE_CONTAINS_OLD)
	{
		Size		datalen = XLogRecGetDataLen(r) - SizeOfHeapDelete;
		Size		tuplelen = datalen - SizeOfHeapHeader;

		Assert(XLogRecGetDataLen(r) > (SizeOfHeapDelete + SizeOfHeapHeader));

		change->data.tp.oldtuple =
			ReorderBufferGetTupleBuf(ctx->reorder, tuplelen);

		DecodeXLogTuple((char *) xlrec + SizeOfHeapDelete,
						datalen, change->data.tp.oldtuple);
	}

	change->data.tp.clear_toast_afterwards = true;

	ReorderBufferQueueChange(ctx->reorder, XLogRecGetXid(r), buf->origptr, change);
}