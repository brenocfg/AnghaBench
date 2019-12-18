#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_5__ {int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  ReorderBufferTXN ;
typedef  TYPE_1__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  OutputPluginPrepareWrite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OutputPluginWrite (TYPE_1__*,int) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pg_decode_message(LogicalDecodingContext *ctx,
				  ReorderBufferTXN *txn, XLogRecPtr lsn, bool transactional,
				  const char *prefix, Size sz, const char *message)
{
	OutputPluginPrepareWrite(ctx, true);
	appendStringInfo(ctx->out, "message: transactional: %d prefix: %s, sz: %zu content:",
					 transactional, prefix, sz);
	appendBinaryStringInfo(ctx->out, message, sz);
	OutputPluginWrite(ctx, true);
}