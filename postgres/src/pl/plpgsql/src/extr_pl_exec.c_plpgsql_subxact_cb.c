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
struct TYPE_4__ {scalar_t__ xact_subxid; struct TYPE_4__* next; int /*<<< orphan*/  stack_econtext; } ;
typedef  scalar_t__ SubXactEvent ;
typedef  scalar_t__ SubTransactionId ;
typedef  TYPE_1__ SimpleEcontextStackEntry ;

/* Variables and functions */
 int /*<<< orphan*/  FreeExprContext (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUBXACT_EVENT_ABORT_SUB ; 
 scalar_t__ SUBXACT_EVENT_COMMIT_SUB ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 TYPE_1__* simple_econtext_stack ; 

void
plpgsql_subxact_cb(SubXactEvent event, SubTransactionId mySubid,
				   SubTransactionId parentSubid, void *arg)
{
	if (event == SUBXACT_EVENT_COMMIT_SUB || event == SUBXACT_EVENT_ABORT_SUB)
	{
		while (simple_econtext_stack != NULL &&
			   simple_econtext_stack->xact_subxid == mySubid)
		{
			SimpleEcontextStackEntry *next;

			FreeExprContext(simple_econtext_stack->stack_econtext,
							(event == SUBXACT_EVENT_COMMIT_SUB));
			next = simple_econtext_stack->next;
			pfree(simple_econtext_stack);
			simple_econtext_stack = next;
		}
	}
}