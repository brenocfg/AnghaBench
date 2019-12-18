#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int16 ;
typedef  int /*<<< orphan*/  Relids ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  PathKey ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprCollation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ordering_op_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_pathkey_from_sortinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

List *
build_expression_pathkey(PlannerInfo *root,
						 Expr *expr,
						 Relids nullable_relids,
						 Oid opno,
						 Relids rel,
						 bool create_it)
{
	List	   *pathkeys;
	Oid			opfamily,
				opcintype;
	int16		strategy;
	PathKey    *cpathkey;

	/* Find the operator in pg_amop --- failure shouldn't happen */
	if (!get_ordering_op_properties(opno,
									&opfamily, &opcintype, &strategy))
		elog(ERROR, "operator %u is not a valid ordering operator",
			 opno);

	cpathkey = make_pathkey_from_sortinfo(root,
										  expr,
										  nullable_relids,
										  opfamily,
										  opcintype,
										  exprCollation((Node *) expr),
										  (strategy == BTGreaterStrategyNumber),
										  (strategy == BTGreaterStrategyNumber),
										  0,
										  rel,
										  create_it);

	if (cpathkey)
		pathkeys = list_make1(cpathkey);
	else
		pathkeys = NIL;

	return pathkeys;
}