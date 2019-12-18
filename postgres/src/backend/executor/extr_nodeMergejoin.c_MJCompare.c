#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_11__ {int /*<<< orphan*/  ssup; scalar_t__ risnull; int /*<<< orphan*/  rdatum; scalar_t__ lisnull; int /*<<< orphan*/  ldatum; } ;
struct TYPE_8__ {TYPE_5__* ps_ExprContext; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_10__ {int mj_NumClauses; scalar_t__ mj_ConstFalseJoin; TYPE_4__* mj_Clauses; TYPE_2__ js; } ;
typedef  TYPE_3__ MergeJoinState ;
typedef  TYPE_4__* MergeJoinClause ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_5__ ExprContext ;

/* Variables and functions */
 int ApplySortComparator (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_5__*) ; 

__attribute__((used)) static int
MJCompare(MergeJoinState *mergestate)
{
	int			result = 0;
	bool		nulleqnull = false;
	ExprContext *econtext = mergestate->js.ps.ps_ExprContext;
	int			i;
	MemoryContext oldContext;

	/*
	 * Call the comparison functions in short-lived context, in case they leak
	 * memory.
	 */
	ResetExprContext(econtext);

	oldContext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

	for (i = 0; i < mergestate->mj_NumClauses; i++)
	{
		MergeJoinClause clause = &mergestate->mj_Clauses[i];

		/*
		 * Special case for NULL-vs-NULL, else use standard comparison.
		 */
		if (clause->lisnull && clause->risnull)
		{
			nulleqnull = true;	/* NULL "=" NULL */
			continue;
		}

		result = ApplySortComparator(clause->ldatum, clause->lisnull,
									 clause->rdatum, clause->risnull,
									 &clause->ssup);

		if (result != 0)
			break;
	}

	/*
	 * If we had any NULL-vs-NULL inputs, we do not want to report that the
	 * tuples are equal.  Instead, if result is still 0, change it to +1. This
	 * will result in advancing the inner side of the join.
	 *
	 * Likewise, if there was a constant-false joinqual, do not report
	 * equality.  We have to check this as part of the mergequals, else the
	 * rescan logic will do the wrong thing.
	 */
	if (result == 0 &&
		(nulleqnull || mergestate->mj_ConstFalseJoin))
		result = 1;

	MemoryContextSwitchTo(oldContext);

	return result;
}