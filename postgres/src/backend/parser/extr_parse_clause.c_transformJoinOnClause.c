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
struct TYPE_7__ {int /*<<< orphan*/  quals; } ;
struct TYPE_6__ {int /*<<< orphan*/ * p_namespace; } ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ JoinExpr ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_KIND_JOIN_ON ; 
 int /*<<< orphan*/  setNamespaceLateralState (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * transformWhereClause (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Node *
transformJoinOnClause(ParseState *pstate, JoinExpr *j, List *namespace)
{
	Node	   *result;
	List	   *save_namespace;

	/*
	 * The namespace that the join expression should see is just the two
	 * subtrees of the JOIN plus any outer references from upper pstate
	 * levels.  Temporarily set this pstate's namespace accordingly.  (We need
	 * not check for refname conflicts, because transformFromClauseItem()
	 * already did.)  All namespace items are marked visible regardless of
	 * LATERAL state.
	 */
	setNamespaceLateralState(namespace, false, true);

	save_namespace = pstate->p_namespace;
	pstate->p_namespace = namespace;

	result = transformWhereClause(pstate, j->quals,
								  EXPR_KIND_JOIN_ON, "JOIN/ON");

	pstate->p_namespace = save_namespace;

	return result;
}