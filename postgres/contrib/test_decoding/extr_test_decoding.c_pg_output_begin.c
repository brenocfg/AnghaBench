#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ include_xids; } ;
typedef  TYPE_1__ TestDecodingData ;
struct TYPE_11__ {int /*<<< orphan*/  out; } ;
struct TYPE_10__ {int /*<<< orphan*/  xid; } ;
typedef  TYPE_2__ ReorderBufferTXN ;
typedef  TYPE_3__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  OutputPluginPrepareWrite (TYPE_3__*,int) ; 
 int /*<<< orphan*/  OutputPluginWrite (TYPE_3__*,int) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pg_output_begin(LogicalDecodingContext *ctx, TestDecodingData *data, ReorderBufferTXN *txn, bool last_write)
{
	OutputPluginPrepareWrite(ctx, last_write);
	if (data->include_xids)
		appendStringInfo(ctx->out, "BEGIN %u", txn->xid);
	else
		appendStringInfoString(ctx->out, "BEGIN");
	OutputPluginWrite(ctx, last_write);
}