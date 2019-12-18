#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  elements; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int opretset; int /*<<< orphan*/  args; int /*<<< orphan*/  inputcollid; int /*<<< orphan*/  opcollid; int /*<<< orphan*/  opresulttype; int /*<<< orphan*/  opfuncid; int /*<<< orphan*/  opno; TYPE_1__ xpr; } ;
struct TYPE_12__ {int /*<<< orphan*/  next; TYPE_2__ opexpr; } ;
struct TYPE_11__ {int /*<<< orphan*/  state_list; void* state; } ;
struct TYPE_10__ {int /*<<< orphan*/  args; int /*<<< orphan*/  inputcollid; int /*<<< orphan*/  opfuncid; int /*<<< orphan*/  opno; } ;
typedef  TYPE_3__ ScalarArrayOpExpr ;
typedef  TYPE_4__* PredIterInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_5__ ArrayExprIterState ;
typedef  TYPE_6__ ArrayExpr ;

/* Variables and functions */
 int /*<<< orphan*/  BOOLOID ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  T_OpExpr ; 
 int /*<<< orphan*/  list_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_head (int /*<<< orphan*/ ) ; 
 scalar_t__ lsecond (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
arrayexpr_startup_fn(Node *clause, PredIterInfo info)
{
	ScalarArrayOpExpr *saop = (ScalarArrayOpExpr *) clause;
	ArrayExprIterState *state;
	ArrayExpr  *arrayexpr;

	/* Create working state struct */
	state = (ArrayExprIterState *) palloc(sizeof(ArrayExprIterState));
	info->state = (void *) state;

	/* Set up a dummy OpExpr to return as the per-item node */
	state->opexpr.xpr.type = T_OpExpr;
	state->opexpr.opno = saop->opno;
	state->opexpr.opfuncid = saop->opfuncid;
	state->opexpr.opresulttype = BOOLOID;
	state->opexpr.opretset = false;
	state->opexpr.opcollid = InvalidOid;
	state->opexpr.inputcollid = saop->inputcollid;
	state->opexpr.args = list_copy(saop->args);

	/* Initialize iteration variable to first member of ArrayExpr */
	arrayexpr = (ArrayExpr *) lsecond(saop->args);
	info->state_list = arrayexpr->elements;
	state->next = list_head(arrayexpr->elements);
}