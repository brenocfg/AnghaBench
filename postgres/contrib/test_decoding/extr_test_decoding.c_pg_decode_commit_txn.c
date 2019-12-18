#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {scalar_t__ include_timestamp; scalar_t__ include_xids; int /*<<< orphan*/  xact_wrote_changes; scalar_t__ skip_empty_xacts; } ;
typedef  TYPE_1__ TestDecodingData ;
struct TYPE_10__ {int /*<<< orphan*/  out; TYPE_1__* output_plugin_private; } ;
struct TYPE_9__ {int /*<<< orphan*/  commit_time; int /*<<< orphan*/  xid; } ;
typedef  TYPE_2__ ReorderBufferTXN ;
typedef  TYPE_3__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  OutputPluginPrepareWrite (TYPE_3__*,int) ; 
 int /*<<< orphan*/  OutputPluginWrite (TYPE_3__*,int) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timestamptz_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pg_decode_commit_txn(LogicalDecodingContext *ctx, ReorderBufferTXN *txn,
					 XLogRecPtr commit_lsn)
{
	TestDecodingData *data = ctx->output_plugin_private;

	if (data->skip_empty_xacts && !data->xact_wrote_changes)
		return;

	OutputPluginPrepareWrite(ctx, true);
	if (data->include_xids)
		appendStringInfo(ctx->out, "COMMIT %u", txn->xid);
	else
		appendStringInfoString(ctx->out, "COMMIT");

	if (data->include_timestamp)
		appendStringInfo(ctx->out, " (at %s)",
						 timestamptz_to_str(txn->commit_time));

	OutputPluginWrite(ctx, true);
}