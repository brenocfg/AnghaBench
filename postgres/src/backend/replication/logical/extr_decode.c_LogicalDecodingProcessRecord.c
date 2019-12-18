#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/ * record; int /*<<< orphan*/  origptr; int /*<<< orphan*/  endptr; } ;
typedef  TYPE_2__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  XLogReaderState ;
struct TYPE_19__ {int /*<<< orphan*/  reorder; TYPE_1__* reader; } ;
struct TYPE_17__ {int /*<<< orphan*/  EndRecPtr; int /*<<< orphan*/  ReadRecPtr; } ;
typedef  int /*<<< orphan*/  RmgrIds ;
typedef  TYPE_3__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeHeap2Op (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DecodeHeapOp (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DecodeLogicalMsgOp (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DecodeStandbyOp (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DecodeXLogOp (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DecodeXactOp (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ERROR ; 
#define  RM_BRIN_ID 150 
#define  RM_BTREE_ID 149 
#define  RM_CLOG_ID 148 
#define  RM_COMMIT_TS_ID 147 
#define  RM_DBASE_ID 146 
#define  RM_GENERIC_ID 145 
#define  RM_GIN_ID 144 
#define  RM_GIST_ID 143 
#define  RM_HASH_ID 142 
#define  RM_HEAP2_ID 141 
#define  RM_HEAP_ID 140 
#define  RM_LOGICALMSG_ID 139 
#define  RM_MULTIXACT_ID 138 
#define  RM_NEXT_ID 137 
#define  RM_RELMAP_ID 136 
#define  RM_REPLORIGIN_ID 135 
#define  RM_SEQ_ID 134 
#define  RM_SMGR_ID 133 
#define  RM_SPGIST_ID 132 
#define  RM_STANDBY_ID 131 
#define  RM_TBLSPC_ID 130 
#define  RM_XACT_ID 129 
#define  RM_XLOG_ID 128 
 int /*<<< orphan*/  ReorderBufferProcessXid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecGetRmid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetXid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
LogicalDecodingProcessRecord(LogicalDecodingContext *ctx, XLogReaderState *record)
{
	XLogRecordBuffer buf;

	buf.origptr = ctx->reader->ReadRecPtr;
	buf.endptr = ctx->reader->EndRecPtr;
	buf.record = record;

	/* cast so we get a warning when new rmgrs are added */
	switch ((RmgrIds) XLogRecGetRmid(record))
	{
			/*
			 * Rmgrs we care about for logical decoding. Add new rmgrs in
			 * rmgrlist.h's order.
			 */
		case RM_XLOG_ID:
			DecodeXLogOp(ctx, &buf);
			break;

		case RM_XACT_ID:
			DecodeXactOp(ctx, &buf);
			break;

		case RM_STANDBY_ID:
			DecodeStandbyOp(ctx, &buf);
			break;

		case RM_HEAP2_ID:
			DecodeHeap2Op(ctx, &buf);
			break;

		case RM_HEAP_ID:
			DecodeHeapOp(ctx, &buf);
			break;

		case RM_LOGICALMSG_ID:
			DecodeLogicalMsgOp(ctx, &buf);
			break;

			/*
			 * Rmgrs irrelevant for logical decoding; they describe stuff not
			 * represented in logical decoding. Add new rmgrs in rmgrlist.h's
			 * order.
			 */
		case RM_SMGR_ID:
		case RM_CLOG_ID:
		case RM_DBASE_ID:
		case RM_TBLSPC_ID:
		case RM_MULTIXACT_ID:
		case RM_RELMAP_ID:
		case RM_BTREE_ID:
		case RM_HASH_ID:
		case RM_GIN_ID:
		case RM_GIST_ID:
		case RM_SEQ_ID:
		case RM_SPGIST_ID:
		case RM_BRIN_ID:
		case RM_COMMIT_TS_ID:
		case RM_REPLORIGIN_ID:
		case RM_GENERIC_ID:
			/* just deal with xid, and done */
			ReorderBufferProcessXid(ctx->reorder, XLogRecGetXid(record),
									buf.origptr);
			break;
		case RM_NEXT_ID:
			elog(ERROR, "unexpected RM_NEXT_ID rmgr_id: %u", (RmgrIds) XLogRecGetRmid(buf.record));
	}
}