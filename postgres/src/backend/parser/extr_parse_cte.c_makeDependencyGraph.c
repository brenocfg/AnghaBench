#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* cte; } ;
struct TYPE_7__ {scalar_t__ ctequery; } ;
struct TYPE_6__ {int numitems; int curitem; scalar_t__ innerwiths; TYPE_5__* items; int /*<<< orphan*/  pstate; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ CteState ;
typedef  TYPE_2__ CommonTableExpr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  TopologicalSort (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  makeDependencyGraphWalker (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
makeDependencyGraph(CteState *cstate)
{
	int			i;

	for (i = 0; i < cstate->numitems; i++)
	{
		CommonTableExpr *cte = cstate->items[i].cte;

		cstate->curitem = i;
		cstate->innerwiths = NIL;
		makeDependencyGraphWalker((Node *) cte->ctequery, cstate);
		Assert(cstate->innerwiths == NIL);
	}

	TopologicalSort(cstate->pstate, cstate->items, cstate->numitems);
}