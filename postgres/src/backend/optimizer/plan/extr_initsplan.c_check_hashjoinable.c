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
struct TYPE_5__ {int /*<<< orphan*/  args; int /*<<< orphan*/  opno; } ;
struct TYPE_4__ {int /*<<< orphan*/  hashjoinoperator; scalar_t__ pseudoconstant; int /*<<< orphan*/ * clause; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  TYPE_2__ OpExpr ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  contain_volatile_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exprType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_opclause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ op_hashjoinable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_hashjoinable(RestrictInfo *restrictinfo)
{
	Expr	   *clause = restrictinfo->clause;
	Oid			opno;
	Node	   *leftarg;

	if (restrictinfo->pseudoconstant)
		return;
	if (!is_opclause(clause))
		return;
	if (list_length(((OpExpr *) clause)->args) != 2)
		return;

	opno = ((OpExpr *) clause)->opno;
	leftarg = linitial(((OpExpr *) clause)->args);

	if (op_hashjoinable(opno, exprType(leftarg)) &&
		!contain_volatile_functions((Node *) clause))
		restrictinfo->hashjoinoperator = opno;
}