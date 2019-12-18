#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* truncate_cb ) (TYPE_6__*,TYPE_2__*,int,int /*<<< orphan*/ *,TYPE_3__*) ;} ;
struct TYPE_20__ {int accept_writes; TYPE_1__ callbacks; int /*<<< orphan*/  write_location; int /*<<< orphan*/  write_xid; int /*<<< orphan*/  fast_forward; } ;
struct TYPE_19__ {char* callback_name; int /*<<< orphan*/  report_location; TYPE_6__* ctx; } ;
struct TYPE_18__ {TYPE_6__* private_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  lsn; } ;
struct TYPE_16__ {int /*<<< orphan*/  xid; } ;
typedef  TYPE_2__ ReorderBufferTXN ;
typedef  TYPE_3__ ReorderBufferChange ;
typedef  TYPE_4__ ReorderBuffer ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_5__ LogicalErrorCallbackState ;
typedef  TYPE_6__ LogicalDecodingContext ;
typedef  TYPE_7__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_7__* error_context_stack ; 
 int /*<<< orphan*/  output_plugin_error_callback ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_2__*,int,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
truncate_cb_wrapper(ReorderBuffer *cache, ReorderBufferTXN *txn,
					int nrelations, Relation relations[], ReorderBufferChange *change)
{
	LogicalDecodingContext *ctx = cache->private_data;
	LogicalErrorCallbackState state;
	ErrorContextCallback errcallback;

	Assert(!ctx->fast_forward);

	if (!ctx->callbacks.truncate_cb)
		return;

	/* Push callback + info on the error context stack */
	state.ctx = ctx;
	state.callback_name = "truncate";
	state.report_location = change->lsn;
	errcallback.callback = output_plugin_error_callback;
	errcallback.arg = (void *) &state;
	errcallback.previous = error_context_stack;
	error_context_stack = &errcallback;

	/* set output state */
	ctx->accept_writes = true;
	ctx->write_xid = txn->xid;

	/*
	 * report this change's lsn so replies from clients can give an up2date
	 * answer. This won't ever be enough (and shouldn't be!) to confirm
	 * receipt of this transaction, but it might allow another transaction's
	 * commit to be confirmed with one message.
	 */
	ctx->write_location = change->lsn;

	ctx->callbacks.truncate_cb(ctx, txn, nrelations, relations, change);

	/* Pop the error context stack */
	error_context_stack = errcallback.previous;
}