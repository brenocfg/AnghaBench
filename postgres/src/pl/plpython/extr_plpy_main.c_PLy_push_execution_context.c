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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * scratch_ctx; int /*<<< orphan*/ * curr_proc; } ;
typedef  TYPE_1__ PLyExecutionContext ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* PLy_execution_contexts ; 
 int /*<<< orphan*/  PortalContext ; 
 int /*<<< orphan*/  TopTransactionContext ; 

__attribute__((used)) static PLyExecutionContext *
PLy_push_execution_context(bool atomic_context)
{
	PLyExecutionContext *context;

	/* Pick a memory context similar to what SPI uses. */
	context = (PLyExecutionContext *)
		MemoryContextAlloc(atomic_context ? TopTransactionContext : PortalContext,
						   sizeof(PLyExecutionContext));
	context->curr_proc = NULL;
	context->scratch_ctx = NULL;
	context->next = PLy_execution_contexts;
	PLy_execution_contexts = context;
	return context;
}