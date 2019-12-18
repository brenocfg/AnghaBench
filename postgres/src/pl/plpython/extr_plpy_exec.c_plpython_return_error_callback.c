#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* curr_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_procedure; } ;
typedef  TYPE_2__ PLyExecutionContext ;

/* Variables and functions */
 TYPE_2__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  errcontext (char*) ; 

__attribute__((used)) static void
plpython_return_error_callback(void *arg)
{
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();

	if (exec_ctx->curr_proc &&
		!exec_ctx->curr_proc->is_procedure)
		errcontext("while creating return value");
}