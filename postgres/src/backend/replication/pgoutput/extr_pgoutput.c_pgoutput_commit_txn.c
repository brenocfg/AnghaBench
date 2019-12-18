#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_6__ {int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  ReorderBufferTXN ;
typedef  TYPE_1__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  OutputPluginPrepareWrite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OutputPluginUpdateProgress (TYPE_1__*) ; 
 int /*<<< orphan*/  OutputPluginWrite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  logicalrep_write_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgoutput_commit_txn(LogicalDecodingContext *ctx, ReorderBufferTXN *txn,
					XLogRecPtr commit_lsn)
{
	OutputPluginUpdateProgress(ctx);

	OutputPluginPrepareWrite(ctx, true);
	logicalrep_write_commit(ctx->out, txn, commit_lsn);
	OutputPluginWrite(ctx, true);
}