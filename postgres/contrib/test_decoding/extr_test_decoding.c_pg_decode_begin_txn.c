#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int xact_wrote_changes; scalar_t__ skip_empty_xacts; } ;
typedef  TYPE_1__ TestDecodingData ;
struct TYPE_7__ {TYPE_1__* output_plugin_private; } ;
typedef  int /*<<< orphan*/  ReorderBufferTXN ;
typedef  TYPE_2__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  pg_output_begin (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pg_decode_begin_txn(LogicalDecodingContext *ctx, ReorderBufferTXN *txn)
{
	TestDecodingData *data = ctx->output_plugin_private;

	data->xact_wrote_changes = false;
	if (data->skip_empty_xacts)
		return;

	pg_output_begin(ctx, data, txn, true);
}