#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct LogicalDecodingContext {int prepared_write; int /*<<< orphan*/  write_xid; int /*<<< orphan*/  write_location; int /*<<< orphan*/  (* prepare_write ) (struct LogicalDecodingContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  accept_writes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct LogicalDecodingContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
OutputPluginPrepareWrite(struct LogicalDecodingContext *ctx, bool last_write)
{
	if (!ctx->accept_writes)
		elog(ERROR, "writes are only accepted in commit, begin and change callbacks");

	ctx->prepare_write(ctx, ctx->write_location, ctx->write_xid, last_write);
	ctx->prepared_write = true;
}