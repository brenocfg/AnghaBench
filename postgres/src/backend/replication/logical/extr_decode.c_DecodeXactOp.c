#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  twophase_xid; } ;
typedef  TYPE_1__ xl_xact_parsed_commit ;
struct TYPE_17__ {int /*<<< orphan*/  twophase_xid; } ;
typedef  TYPE_2__ xl_xact_parsed_abort ;
typedef  int /*<<< orphan*/  xl_xact_commit ;
struct TYPE_18__ {int nsubxacts; int /*<<< orphan*/  xtop; int /*<<< orphan*/ * xsub; } ;
typedef  TYPE_3__ xl_xact_assignment ;
typedef  int /*<<< orphan*/  xl_xact_abort ;
typedef  int uint8 ;
struct TYPE_19__ {int /*<<< orphan*/  origptr; int /*<<< orphan*/ * record; } ;
typedef  TYPE_4__ XLogRecordBuffer ;
typedef  int /*<<< orphan*/  XLogReaderState ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_20__ {int /*<<< orphan*/ * reorder; int /*<<< orphan*/ * snapshot_builder; } ;
typedef  int /*<<< orphan*/  SnapBuild ;
typedef  int /*<<< orphan*/  ReorderBuffer ;
typedef  TYPE_5__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeAbort (TYPE_5__*,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DecodeCommit (TYPE_5__*,TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ParseAbortRecord (int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ParseCommitRecord (int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ReorderBufferAssignChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferProcessXid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SNAPBUILD_FULL_SNAPSHOT ; 
 scalar_t__ SnapBuildCurrentState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
#define  XLOG_XACT_ABORT 133 
#define  XLOG_XACT_ABORT_PREPARED 132 
#define  XLOG_XACT_ASSIGNMENT 131 
#define  XLOG_XACT_COMMIT 130 
#define  XLOG_XACT_COMMIT_PREPARED 129 
 int XLOG_XACT_OPMASK ; 
#define  XLOG_XACT_PREPARE 128 
 scalar_t__ XLogRecGetData (int /*<<< orphan*/ *) ; 
 int XLogRecGetInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLogRecGetXid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
DecodeXactOp(LogicalDecodingContext *ctx, XLogRecordBuffer *buf)
{
	SnapBuild  *builder = ctx->snapshot_builder;
	ReorderBuffer *reorder = ctx->reorder;
	XLogReaderState *r = buf->record;
	uint8		info = XLogRecGetInfo(r) & XLOG_XACT_OPMASK;

	/*
	 * If the snapshot isn't yet fully built, we cannot decode anything, so
	 * bail out.
	 *
	 * However, it's critical to process XLOG_XACT_ASSIGNMENT records even
	 * when the snapshot is being built: it is possible to get later records
	 * that require subxids to be properly assigned.
	 */
	if (SnapBuildCurrentState(builder) < SNAPBUILD_FULL_SNAPSHOT &&
		info != XLOG_XACT_ASSIGNMENT)
		return;

	switch (info)
	{
		case XLOG_XACT_COMMIT:
		case XLOG_XACT_COMMIT_PREPARED:
			{
				xl_xact_commit *xlrec;
				xl_xact_parsed_commit parsed;
				TransactionId xid;

				xlrec = (xl_xact_commit *) XLogRecGetData(r);
				ParseCommitRecord(XLogRecGetInfo(buf->record), xlrec, &parsed);

				if (!TransactionIdIsValid(parsed.twophase_xid))
					xid = XLogRecGetXid(r);
				else
					xid = parsed.twophase_xid;

				DecodeCommit(ctx, buf, &parsed, xid);
				break;
			}
		case XLOG_XACT_ABORT:
		case XLOG_XACT_ABORT_PREPARED:
			{
				xl_xact_abort *xlrec;
				xl_xact_parsed_abort parsed;
				TransactionId xid;

				xlrec = (xl_xact_abort *) XLogRecGetData(r);
				ParseAbortRecord(XLogRecGetInfo(buf->record), xlrec, &parsed);

				if (!TransactionIdIsValid(parsed.twophase_xid))
					xid = XLogRecGetXid(r);
				else
					xid = parsed.twophase_xid;

				DecodeAbort(ctx, buf, &parsed, xid);
				break;
			}
		case XLOG_XACT_ASSIGNMENT:
			{
				xl_xact_assignment *xlrec;
				int			i;
				TransactionId *sub_xid;

				xlrec = (xl_xact_assignment *) XLogRecGetData(r);

				sub_xid = &xlrec->xsub[0];

				for (i = 0; i < xlrec->nsubxacts; i++)
				{
					ReorderBufferAssignChild(reorder, xlrec->xtop,
											 *(sub_xid++), buf->origptr);
				}
				break;
			}
		case XLOG_XACT_PREPARE:

			/*
			 * Currently decoding ignores PREPARE TRANSACTION and will just
			 * decode the transaction when the COMMIT PREPARED is sent or
			 * throw away the transaction's contents when a ROLLBACK PREPARED
			 * is received. In the future we could add code to expose prepared
			 * transactions in the changestream allowing for a kind of
			 * distributed 2PC.
			 */
			ReorderBufferProcessXid(reorder, XLogRecGetXid(r), buf->origptr);
			break;
		default:
			elog(ERROR, "unexpected RM_XACT_ID record type: %u", info);
	}
}