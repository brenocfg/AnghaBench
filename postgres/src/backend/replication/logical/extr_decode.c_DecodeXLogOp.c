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
typedef  int uint8 ;
struct TYPE_5__ {int /*<<< orphan*/  origptr; int /*<<< orphan*/  record; } ;
typedef  TYPE_1__ XLogRecordBuffer ;
struct TYPE_6__ {int /*<<< orphan*/  reorder; int /*<<< orphan*/ * snapshot_builder; } ;
typedef  int /*<<< orphan*/  SnapBuild ;
typedef  TYPE_2__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ReorderBufferProcessXid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapBuildSerializationPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  XLOG_BACKUP_END 139 
#define  XLOG_CHECKPOINT_ONLINE 138 
#define  XLOG_CHECKPOINT_SHUTDOWN 137 
#define  XLOG_END_OF_RECOVERY 136 
#define  XLOG_FPI 135 
#define  XLOG_FPI_FOR_HINT 134 
#define  XLOG_FPW_CHANGE 133 
#define  XLOG_NEXTOID 132 
#define  XLOG_NOOP 131 
#define  XLOG_PARAMETER_CHANGE 130 
#define  XLOG_RESTORE_POINT 129 
#define  XLOG_SWITCH 128 
 int XLR_INFO_MASK ; 
 int XLogRecGetInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecGetXid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
DecodeXLogOp(LogicalDecodingContext *ctx, XLogRecordBuffer *buf)
{
	SnapBuild  *builder = ctx->snapshot_builder;
	uint8		info = XLogRecGetInfo(buf->record) & ~XLR_INFO_MASK;

	ReorderBufferProcessXid(ctx->reorder, XLogRecGetXid(buf->record),
							buf->origptr);

	switch (info)
	{
			/* this is also used in END_OF_RECOVERY checkpoints */
		case XLOG_CHECKPOINT_SHUTDOWN:
		case XLOG_END_OF_RECOVERY:
			SnapBuildSerializationPoint(builder, buf->origptr);

			break;
		case XLOG_CHECKPOINT_ONLINE:

			/*
			 * a RUNNING_XACTS record will have been logged near to this, we
			 * can restart from there.
			 */
			break;
		case XLOG_NOOP:
		case XLOG_NEXTOID:
		case XLOG_SWITCH:
		case XLOG_BACKUP_END:
		case XLOG_PARAMETER_CHANGE:
		case XLOG_RESTORE_POINT:
		case XLOG_FPW_CHANGE:
		case XLOG_FPI_FOR_HINT:
		case XLOG_FPI:
			break;
		default:
			elog(ERROR, "unexpected RM_XLOG_ID record type: %u", info);
	}
}