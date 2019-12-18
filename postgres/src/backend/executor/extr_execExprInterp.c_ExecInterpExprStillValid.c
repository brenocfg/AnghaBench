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
struct TYPE_6__ {int /*<<< orphan*/  (* evalfunc ) (TYPE_1__*,int /*<<< orphan*/ *,int*) ;scalar_t__ evalfunc_private; } ;
typedef  int /*<<< orphan*/  (* ExprStateEvalFunc ) (TYPE_1__*,int /*<<< orphan*/ *,int*) ;
typedef  TYPE_1__ ExprState ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CheckExprStillValid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 

Datum
ExecInterpExprStillValid(ExprState *state, ExprContext *econtext, bool *isNull)
{
	/*
	 * First time through, check whether attribute matches Var.  Might not be
	 * ok anymore, due to schema changes.
	 */
	CheckExprStillValid(state, econtext);

	/* skip the check during further executions */
	state->evalfunc = (ExprStateEvalFunc) state->evalfunc_private;

	/* and actually execute */
	return state->evalfunc(state, econtext, isNull);
}