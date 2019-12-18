#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ context; } ;
struct TYPE_7__ {int op; scalar_t__ lockingClause; scalar_t__ limitCount; scalar_t__ limitOffset; scalar_t__ sortClause; scalar_t__ rarg; scalar_t__ larg; int /*<<< orphan*/  all; } ;
typedef  TYPE_1__ SelectStmt ;
typedef  scalar_t__ RecursionContext ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ CteState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 void* RECURSION_EXCEPT ; 
 scalar_t__ RECURSION_INTERSECT ; 
 scalar_t__ RECURSION_OK ; 
#define  SETOP_EXCEPT 131 
#define  SETOP_INTERSECT 130 
#define  SETOP_NONE 129 
#define  SETOP_UNION 128 
 int /*<<< orphan*/  checkWellFormedRecursionWalker (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  raw_expression_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,TYPE_2__*),void*) ; 

__attribute__((used)) static void
checkWellFormedSelectStmt(SelectStmt *stmt, CteState *cstate)
{
	RecursionContext save_context = cstate->context;

	if (save_context != RECURSION_OK)
	{
		/* just recurse without changing state */
		raw_expression_tree_walker((Node *) stmt,
								   checkWellFormedRecursionWalker,
								   (void *) cstate);
	}
	else
	{
		switch (stmt->op)
		{
			case SETOP_NONE:
			case SETOP_UNION:
				raw_expression_tree_walker((Node *) stmt,
										   checkWellFormedRecursionWalker,
										   (void *) cstate);
				break;
			case SETOP_INTERSECT:
				if (stmt->all)
					cstate->context = RECURSION_INTERSECT;
				checkWellFormedRecursionWalker((Node *) stmt->larg,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->rarg,
											   cstate);
				cstate->context = save_context;
				checkWellFormedRecursionWalker((Node *) stmt->sortClause,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->limitOffset,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->limitCount,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->lockingClause,
											   cstate);
				/* stmt->withClause is intentionally ignored here */
				break;
			case SETOP_EXCEPT:
				if (stmt->all)
					cstate->context = RECURSION_EXCEPT;
				checkWellFormedRecursionWalker((Node *) stmt->larg,
											   cstate);
				cstate->context = RECURSION_EXCEPT;
				checkWellFormedRecursionWalker((Node *) stmt->rarg,
											   cstate);
				cstate->context = save_context;
				checkWellFormedRecursionWalker((Node *) stmt->sortClause,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->limitOffset,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->limitCount,
											   cstate);
				checkWellFormedRecursionWalker((Node *) stmt->lockingClause,
											   cstate);
				/* stmt->withClause is intentionally ignored here */
				break;
			default:
				elog(ERROR, "unrecognized set op: %d",
					 (int) stmt->op);
		}
	}
}