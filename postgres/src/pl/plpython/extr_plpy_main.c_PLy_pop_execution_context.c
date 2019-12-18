#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ scratch_ctx; struct TYPE_4__* next; } ;
typedef  TYPE_1__ PLyExecutionContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextDelete (scalar_t__) ; 
 TYPE_1__* PLy_execution_contexts ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
PLy_pop_execution_context(void)
{
	PLyExecutionContext *context = PLy_execution_contexts;

	if (context == NULL)
		elog(ERROR, "no Python function is currently executing");

	PLy_execution_contexts = context->next;

	if (context->scratch_ctx)
		MemoryContextDelete(context->scratch_ctx);
	pfree(context);
}