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
struct LogicalDecodingContext {int /*<<< orphan*/  write_xid; int /*<<< orphan*/  write_location; int /*<<< orphan*/  (* update_progress ) (struct LogicalDecodingContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct LogicalDecodingContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
OutputPluginUpdateProgress(struct LogicalDecodingContext *ctx)
{
	if (!ctx->update_progress)
		return;

	ctx->update_progress(ctx, ctx->write_location, ctx->write_xid);
}