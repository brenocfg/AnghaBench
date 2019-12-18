#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ curr_proc; } ;
typedef  TYPE_1__ PLyExecutionContext ;

/* Variables and functions */
 TYPE_1__* PLy_current_execution_context () ; 
 int /*<<< orphan*/  errcontext (char*) ; 

__attribute__((used)) static void
plpython_trigger_error_callback(void *arg)
{
	PLyExecutionContext *exec_ctx = PLy_current_execution_context();

	if (exec_ctx->curr_proc)
		errcontext("while modifying trigger row");
}