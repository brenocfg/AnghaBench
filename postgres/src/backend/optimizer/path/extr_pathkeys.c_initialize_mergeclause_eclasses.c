#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  inputcollid; int /*<<< orphan*/  opno; } ;
struct TYPE_4__ {int /*<<< orphan*/  mergeopfamilies; int /*<<< orphan*/  nullable_relids; int /*<<< orphan*/ * right_ec; int /*<<< orphan*/ * left_ec; int /*<<< orphan*/ * clause; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ OpExpr ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  NIL ; 
 void* get_eclass_for_sort_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_leftop (int /*<<< orphan*/ *) ; 
 scalar_t__ get_rightop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_input_types (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
initialize_mergeclause_eclasses(PlannerInfo *root, RestrictInfo *restrictinfo)
{
	Expr	   *clause = restrictinfo->clause;
	Oid			lefttype,
				righttype;

	/* Should be a mergeclause ... */
	Assert(restrictinfo->mergeopfamilies != NIL);
	/* ... with links not yet set */
	Assert(restrictinfo->left_ec == NULL);
	Assert(restrictinfo->right_ec == NULL);

	/* Need the declared input types of the operator */
	op_input_types(((OpExpr *) clause)->opno, &lefttype, &righttype);

	/* Find or create a matching EquivalenceClass for each side */
	restrictinfo->left_ec =
		get_eclass_for_sort_expr(root,
								 (Expr *) get_leftop(clause),
								 restrictinfo->nullable_relids,
								 restrictinfo->mergeopfamilies,
								 lefttype,
								 ((OpExpr *) clause)->inputcollid,
								 0,
								 NULL,
								 true);
	restrictinfo->right_ec =
		get_eclass_for_sort_expr(root,
								 (Expr *) get_rightop(clause),
								 restrictinfo->nullable_relids,
								 restrictinfo->mergeopfamilies,
								 righttype,
								 ((OpExpr *) clause)->inputcollid,
								 0,
								 NULL,
								 true);
}