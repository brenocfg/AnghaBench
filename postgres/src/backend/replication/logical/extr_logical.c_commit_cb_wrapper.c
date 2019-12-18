#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_17__ {struct TYPE_17__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* commit_cb ) (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int accept_writes; TYPE_1__ callbacks; int /*<<< orphan*/  write_location; int /*<<< orphan*/  write_xid; int /*<<< orphan*/  fast_forward; } ;
struct TYPE_15__ {char* callback_name; int /*<<< orphan*/  report_location; TYPE_5__* ctx; } ;
struct TYPE_14__ {TYPE_5__* private_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  end_lsn; int /*<<< orphan*/  xid; int /*<<< orphan*/  final_lsn; } ;
typedef  TYPE_2__ ReorderBufferTXN ;
typedef  TYPE_3__ ReorderBuffer ;
typedef  TYPE_4__ LogicalErrorCallbackState ;
typedef  TYPE_5__ LogicalDecodingContext ;
typedef  TYPE_6__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_6__* error_context_stack ; 
 int /*<<< orphan*/  output_plugin_error_callback ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
commit_cb_wrapper(ReorderBuffer *cache, ReorderBufferTXN *txn,
				  XLogRecPtr commit_lsn)
{
	LogicalDecodingContext *ctx = cache->private_data;
	LogicalErrorCallbackState state;
	ErrorContextCallback errcallback;

	Assert(!ctx->fast_forward);

	/* Push callback + info on the error context stack */
	state.ctx = ctx;
	state.callback_name = "commit";
	state.report_location = txn->final_lsn; /* beginning of commit record */
	errcallback.callback = output_plugin_error_callback;
	errcallback.arg = (void *) &state;
	errcallback.previous = error_context_stack;
	error_context_stack = &errcallback;

	/* set output state */
	ctx->accept_writes = true;
	ctx->write_xid = txn->xid;
	ctx->write_location = txn->end_lsn; /* points to the end of the record */

	/* do the actual work: call callback */
	ctx->callbacks.commit_cb(ctx, txn, commit_lsn);

	/* Pop the error context stack */
	error_context_stack = errcallback.previous;
}