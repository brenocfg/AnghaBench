#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  root ;
typedef  int /*<<< orphan*/  glob ;
struct TYPE_6__ {int /*<<< orphan*/ * invalItems; int /*<<< orphan*/ * relationOids; struct TYPE_6__* glob; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ PlannerInfo ;
typedef  TYPE_1__ PlannerGlobal ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* NIL ; 
 int /*<<< orphan*/  T_PlannerGlobal ; 
 int /*<<< orphan*/  T_PlannerInfo ; 
 int /*<<< orphan*/ * eval_const_expressions (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_query_dependencies_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fix_opfuncids (int /*<<< orphan*/ *) ; 

Expr *
expression_planner_with_deps(Expr *expr,
							 List **relationOids,
							 List **invalItems)
{
	Node	   *result;
	PlannerGlobal glob;
	PlannerInfo root;

	/* Make up dummy planner state so we can use setrefs machinery */
	MemSet(&glob, 0, sizeof(glob));
	glob.type = T_PlannerGlobal;
	glob.relationOids = NIL;
	glob.invalItems = NIL;

	MemSet(&root, 0, sizeof(root));
	root.type = T_PlannerInfo;
	root.glob = &glob;

	/*
	 * Convert named-argument function calls, insert default arguments and
	 * simplify constant subexprs.  Collect identities of inlined functions
	 * and elided domains, too.
	 */
	result = eval_const_expressions(&root, (Node *) expr);

	/* Fill in opfuncid values if missing */
	fix_opfuncids(result);

	/*
	 * Now walk the finished expression to find anything else we ought to
	 * record as an expression dependency.
	 */
	(void) extract_query_dependencies_walker(result, &root);

	*relationOids = glob.relationOids;
	*invalItems = glob.invalItems;

	return (Expr *) result;
}