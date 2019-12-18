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
typedef  void* XLogRecPtr ;
struct TYPE_17__ {struct TYPE_17__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* message_cb ) (TYPE_5__*,TYPE_2__*,void*,int,char const*,int /*<<< orphan*/ ,char const*) ;} ;
struct TYPE_16__ {int accept_writes; TYPE_1__ callbacks; void* write_location; int /*<<< orphan*/  write_xid; int /*<<< orphan*/  fast_forward; } ;
struct TYPE_15__ {char* callback_name; void* report_location; TYPE_5__* ctx; } ;
struct TYPE_14__ {TYPE_5__* private_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  xid; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__ ReorderBufferTXN ;
typedef  TYPE_3__ ReorderBuffer ;
typedef  TYPE_4__ LogicalErrorCallbackState ;
typedef  TYPE_5__ LogicalDecodingContext ;
typedef  TYPE_6__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 TYPE_6__* error_context_stack ; 
 int /*<<< orphan*/  output_plugin_error_callback ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_2__*,void*,int,char const*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
message_cb_wrapper(ReorderBuffer *cache, ReorderBufferTXN *txn,
				   XLogRecPtr message_lsn, bool transactional,
				   const char *prefix, Size message_size, const char *message)
{
	LogicalDecodingContext *ctx = cache->private_data;
	LogicalErrorCallbackState state;
	ErrorContextCallback errcallback;

	Assert(!ctx->fast_forward);

	if (ctx->callbacks.message_cb == NULL)
		return;

	/* Push callback + info on the error context stack */
	state.ctx = ctx;
	state.callback_name = "message";
	state.report_location = message_lsn;
	errcallback.callback = output_plugin_error_callback;
	errcallback.arg = (void *) &state;
	errcallback.previous = error_context_stack;
	error_context_stack = &errcallback;

	/* set output state */
	ctx->accept_writes = true;
	ctx->write_xid = txn != NULL ? txn->xid : InvalidTransactionId;
	ctx->write_location = message_lsn;

	/* do the actual work: call callback */
	ctx->callbacks.message_cb(ctx, txn, message_lsn, transactional, prefix,
							  message_size, message);

	/* Pop the error context stack */
	error_context_stack = errcallback.previous;
}