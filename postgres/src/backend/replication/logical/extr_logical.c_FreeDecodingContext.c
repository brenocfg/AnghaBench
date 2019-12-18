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
struct TYPE_5__ {int /*<<< orphan*/ * shutdown_cb; } ;
struct TYPE_6__ {int /*<<< orphan*/  context; int /*<<< orphan*/  reader; int /*<<< orphan*/  snapshot_builder; int /*<<< orphan*/  reorder; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  FreeSnapshotBuilder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogReaderFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_cb_wrapper (TYPE_2__*) ; 

void
FreeDecodingContext(LogicalDecodingContext *ctx)
{
	if (ctx->callbacks.shutdown_cb != NULL)
		shutdown_cb_wrapper(ctx);

	ReorderBufferFree(ctx->reorder);
	FreeSnapshotBuilder(ctx->snapshot_builder);
	XLogReaderFree(ctx->reader);
	MemoryContextDelete(ctx->context);
}