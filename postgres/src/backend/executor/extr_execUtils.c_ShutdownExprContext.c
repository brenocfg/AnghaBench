#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ecxt_callbacks; int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ) ;struct TYPE_5__* next; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ExprContext_CB ;
typedef  TYPE_2__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ShutdownExprContext(ExprContext *econtext, bool isCommit)
{
	ExprContext_CB *ecxt_callback;
	MemoryContext oldcontext;

	/* Fast path in normal case where there's nothing to do. */
	if (econtext->ecxt_callbacks == NULL)
		return;

	/*
	 * Call the callbacks in econtext's per-tuple context.  This ensures that
	 * any memory they might leak will get cleaned up.
	 */
	oldcontext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

	/*
	 * Call each callback function in reverse registration order.
	 */
	while ((ecxt_callback = econtext->ecxt_callbacks) != NULL)
	{
		econtext->ecxt_callbacks = ecxt_callback->next;
		if (isCommit)
			ecxt_callback->function(ecxt_callback->arg);
		pfree(ecxt_callback);
	}

	MemoryContextSwitchTo(oldcontext);
}