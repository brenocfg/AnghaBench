#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ is_procedure; } ;
struct TYPE_3__ {TYPE_2__* curr_proc; } ;
typedef  TYPE_1__ PLyExecutionContext ;

/* Variables and functions */
 int /*<<< orphan*/  PLy_procedure_name (TYPE_2__*) ; 
 int /*<<< orphan*/  errcontext (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plpython_error_callback(void *arg)
{
	PLyExecutionContext *exec_ctx = (PLyExecutionContext *) arg;

	if (exec_ctx->curr_proc)
	{
		if (exec_ctx->curr_proc->is_procedure)
			errcontext("PL/Python procedure \"%s\"",
					   PLy_procedure_name(exec_ctx->curr_proc));
		else
			errcontext("PL/Python function \"%s\"",
					   PLy_procedure_name(exec_ctx->curr_proc));
	}
}