#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * eval_econtext; } ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/ * stack_econtext; } ;
typedef  TYPE_1__ SimpleEcontextStackEntry ;
typedef  TYPE_2__ PLpgSQL_execstate ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FreeExprContext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 TYPE_1__* simple_econtext_stack ; 

__attribute__((used)) static void
plpgsql_destroy_econtext(PLpgSQL_execstate *estate)
{
	SimpleEcontextStackEntry *next;

	Assert(simple_econtext_stack != NULL);
	Assert(simple_econtext_stack->stack_econtext == estate->eval_econtext);

	next = simple_econtext_stack->next;
	pfree(simple_econtext_stack);
	simple_econtext_stack = next;

	FreeExprContext(estate->eval_econtext, true);
	estate->eval_econtext = NULL;
}