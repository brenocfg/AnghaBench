#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_15__ {int /*<<< orphan*/  origptr; int /*<<< orphan*/  record; } ;
typedef  TYPE_1__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_16__ {int /*<<< orphan*/  reorder; scalar_t__ fast_forward; int /*<<< orphan*/ * snapshot_builder; } ;
typedef  int /*<<< orphan*/  SnapBuild ;
typedef  TYPE_2__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeDelete (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DecodeInsert (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DecodeSpecConfirm (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DecodeTruncate (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DecodeUpdate (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ReorderBufferProcessXid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferXidSetCatalogChanges (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SNAPBUILD_FULL_SNAPSHOT ; 
 scalar_t__ SnapBuildCurrentState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SnapBuildProcessChange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
#define  XLOG_HEAP_CONFIRM 135 
#define  XLOG_HEAP_DELETE 134 
#define  XLOG_HEAP_HOT_UPDATE 133 
#define  XLOG_HEAP_INPLACE 132 
#define  XLOG_HEAP_INSERT 131 
#define  XLOG_HEAP_LOCK 130 
 int XLOG_HEAP_OPMASK ; 
#define  XLOG_HEAP_TRUNCATE 129 
#define  XLOG_HEAP_UPDATE 128 
 int XLogRecGetInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecGetXid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
DecodeHeapOp(LogicalDecodingContext *ctx, XLogRecordBuffer *buf)
{
	uint8		info = XLogRecGetInfo(buf->record) & XLOG_HEAP_OPMASK;
	TransactionId xid = XLogRecGetXid(buf->record);
	SnapBuild  *builder = ctx->snapshot_builder;

	ReorderBufferProcessXid(ctx->reorder, xid, buf->origptr);

	/*
	 * If we don't have snapshot or we are just fast-forwarding, there is no
	 * point in decoding data changes.
	 */
	if (SnapBuildCurrentState(builder) < SNAPBUILD_FULL_SNAPSHOT ||
		ctx->fast_forward)
		return;

	switch (info)
	{
		case XLOG_HEAP_INSERT:
			if (SnapBuildProcessChange(builder, xid, buf->origptr))
				DecodeInsert(ctx, buf);
			break;

			/*
			 * Treat HOT update as normal updates. There is no useful
			 * information in the fact that we could make it a HOT update
			 * locally and the WAL layout is compatible.
			 */
		case XLOG_HEAP_HOT_UPDATE:
		case XLOG_HEAP_UPDATE:
			if (SnapBuildProcessChange(builder, xid, buf->origptr))
				DecodeUpdate(ctx, buf);
			break;

		case XLOG_HEAP_DELETE:
			if (SnapBuildProcessChange(builder, xid, buf->origptr))
				DecodeDelete(ctx, buf);
			break;

		case XLOG_HEAP_TRUNCATE:
			if (SnapBuildProcessChange(builder, xid, buf->origptr))
				DecodeTruncate(ctx, buf);
			break;

		case XLOG_HEAP_INPLACE:

			/*
			 * Inplace updates are only ever performed on catalog tuples and
			 * can, per definition, not change tuple visibility.  Since we
			 * don't decode catalog tuples, we're not interested in the
			 * record's contents.
			 *
			 * In-place updates can be used either by XID-bearing transactions
			 * (e.g.  in CREATE INDEX CONCURRENTLY) or by XID-less
			 * transactions (e.g.  VACUUM).  In the former case, the commit
			 * record will include cache invalidations, so we mark the
			 * transaction as catalog modifying here. Currently that's
			 * redundant because the commit will do that as well, but once we
			 * support decoding in-progress relations, this will be important.
			 */
			if (!TransactionIdIsValid(xid))
				break;

			SnapBuildProcessChange(builder, xid, buf->origptr);
			ReorderBufferXidSetCatalogChanges(ctx->reorder, xid, buf->origptr);
			break;

		case XLOG_HEAP_CONFIRM:
			if (SnapBuildProcessChange(builder, xid, buf->origptr))
				DecodeSpecConfirm(ctx, buf);
			break;

		case XLOG_HEAP_LOCK:
			/* we don't care about row level locks for now */
			break;

		default:
			elog(ERROR, "unexpected RM_HEAP_ID record type: %u", info);
			break;
	}
}