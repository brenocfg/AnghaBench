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
struct TYPE_6__ {int /*<<< orphan*/  eval_econtext; int /*<<< orphan*/ * simple_eval_estate; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  xact_subxid; int /*<<< orphan*/  stack_econtext; } ;
typedef  TYPE_1__ SimpleEcontextStackEntry ;
typedef  TYPE_2__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateExecutorState () ; 
 int /*<<< orphan*/  CreateExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 int /*<<< orphan*/ * shared_simple_eval_estate ; 
 TYPE_1__* simple_econtext_stack ; 

__attribute__((used)) static void
plpgsql_create_econtext(PLpgSQL_execstate *estate)
{
	SimpleEcontextStackEntry *entry;

	/*
	 * Create an EState for evaluation of simple expressions, if there's not
	 * one already in the current transaction.  The EState is made a child of
	 * TopTransactionContext so it will have the right lifespan.
	 *
	 * Note that this path is never taken when executing a DO block; the
	 * required EState was already made by plpgsql_inline_handler.
	 */
	if (estate->simple_eval_estate == NULL)
	{
		MemoryContext oldcontext;

		if (shared_simple_eval_estate == NULL)
		{
			oldcontext = MemoryContextSwitchTo(TopTransactionContext);
			shared_simple_eval_estate = CreateExecutorState();
			MemoryContextSwitchTo(oldcontext);
		}
		estate->simple_eval_estate = shared_simple_eval_estate;
	}

	/*
	 * Create a child econtext for the current function.
	 */
	estate->eval_econtext = CreateExprContext(estate->simple_eval_estate);

	/*
	 * Make a stack entry so we can clean up the econtext at subxact end.
	 * Stack entries are kept in TopTransactionContext for simplicity.
	 */
	entry = (SimpleEcontextStackEntry *)
		MemoryContextAlloc(TopTransactionContext,
						   sizeof(SimpleEcontextStackEntry));

	entry->stack_econtext = estate->eval_econtext;
	entry->xact_subxid = GetCurrentSubTransactionId();

	entry->next = simple_econtext_stack;
	simple_econtext_stack = entry;
}