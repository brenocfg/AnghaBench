#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* previous; void* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* shutdown_cb ) (TYPE_3__*) ;} ;
struct TYPE_10__ {int accept_writes; TYPE_1__ callbacks; int /*<<< orphan*/  fast_forward; } ;
struct TYPE_9__ {char* callback_name; int /*<<< orphan*/  report_location; TYPE_3__* ctx; } ;
typedef  TYPE_2__ LogicalErrorCallbackState ;
typedef  TYPE_3__ LogicalDecodingContext ;
typedef  TYPE_4__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 TYPE_4__* error_context_stack ; 
 int /*<<< orphan*/  output_plugin_error_callback ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
shutdown_cb_wrapper(LogicalDecodingContext *ctx)
{
	LogicalErrorCallbackState state;
	ErrorContextCallback errcallback;

	Assert(!ctx->fast_forward);

	/* Push callback + info on the error context stack */
	state.ctx = ctx;
	state.callback_name = "shutdown";
	state.report_location = InvalidXLogRecPtr;
	errcallback.callback = output_plugin_error_callback;
	errcallback.arg = (void *) &state;
	errcallback.previous = error_context_stack;
	error_context_stack = &errcallback;

	/* set output state */
	ctx->accept_writes = false;

	/* do the actual work: call callback */
	ctx->callbacks.shutdown_cb(ctx);

	/* Pop the error context stack */
	error_context_stack = errcallback.previous;
}