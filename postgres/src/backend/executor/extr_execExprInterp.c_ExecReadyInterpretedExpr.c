#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_7__ {TYPE_1__ casetest; } ;
struct TYPE_9__ {scalar_t__ opcode; TYPE_2__ d; } ;
struct TYPE_8__ {int steps_len; int flags; void* evalfunc_private; TYPE_4__* steps; int /*<<< orphan*/  evalfunc; } ;
typedef  TYPE_3__ ExprState ;
typedef  TYPE_4__ ExprEvalStep ;
typedef  scalar_t__ ExprEvalOp ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EEOP_ASSIGN_INNER_VAR ; 
 scalar_t__ EEOP_ASSIGN_OUTER_VAR ; 
 scalar_t__ EEOP_ASSIGN_SCAN_VAR ; 
 scalar_t__ EEOP_CASE_TESTVAL ; 
 scalar_t__ EEOP_CONST ; 
 scalar_t__ EEOP_DONE ; 
 scalar_t__ EEOP_FUNCEXPR_STRICT ; 
 scalar_t__ EEOP_INNER_FETCHSOME ; 
 scalar_t__ EEOP_INNER_VAR ; 
 scalar_t__ EEOP_OUTER_FETCHSOME ; 
 scalar_t__ EEOP_OUTER_VAR ; 
 scalar_t__ EEOP_SCAN_FETCHSOME ; 
 scalar_t__ EEOP_SCAN_VAR ; 
 int EEO_FLAG_DIRECT_THREADED ; 
 int EEO_FLAG_INTERPRETER_INITIALIZED ; 
 scalar_t__ EEO_OPCODE (scalar_t__) ; 
 int /*<<< orphan*/  ExecInitInterpreter () ; 
 scalar_t__ ExecInterpExpr ; 
 int /*<<< orphan*/  ExecInterpExprStillValid ; 
 scalar_t__ ExecJustApplyFuncToCase ; 
 scalar_t__ ExecJustAssignInnerVar ; 
 scalar_t__ ExecJustAssignInnerVarVirt ; 
 scalar_t__ ExecJustAssignOuterVar ; 
 scalar_t__ ExecJustAssignOuterVarVirt ; 
 scalar_t__ ExecJustAssignScanVar ; 
 scalar_t__ ExecJustAssignScanVarVirt ; 
 scalar_t__ ExecJustConst ; 
 scalar_t__ ExecJustInnerVar ; 
 scalar_t__ ExecJustInnerVarVirt ; 
 scalar_t__ ExecJustOuterVar ; 
 scalar_t__ ExecJustOuterVarVirt ; 
 scalar_t__ ExecJustScanVar ; 
 scalar_t__ ExecJustScanVarVirt ; 

void
ExecReadyInterpretedExpr(ExprState *state)
{
	/* Ensure one-time interpreter setup has been done */
	ExecInitInterpreter();

	/* Simple validity checks on expression */
	Assert(state->steps_len >= 1);
	Assert(state->steps[state->steps_len - 1].opcode == EEOP_DONE);

	/*
	 * Don't perform redundant initialization. This is unreachable in current
	 * cases, but might be hit if there's additional expression evaluation
	 * methods that rely on interpreted execution to work.
	 */
	if (state->flags & EEO_FLAG_INTERPRETER_INITIALIZED)
		return;

	/*
	 * First time through, check whether attribute matches Var.  Might not be
	 * ok anymore, due to schema changes. We do that by setting up a callback
	 * that does checking on the first call, which then sets the evalfunc
	 * callback to the actual method of execution.
	 */
	state->evalfunc = ExecInterpExprStillValid;

	/* DIRECT_THREADED should not already be set */
	Assert((state->flags & EEO_FLAG_DIRECT_THREADED) == 0);

	/*
	 * There shouldn't be any errors before the expression is fully
	 * initialized, and even if so, it'd lead to the expression being
	 * abandoned.  So we can set the flag now and save some code.
	 */
	state->flags |= EEO_FLAG_INTERPRETER_INITIALIZED;

	/*
	 * Select fast-path evalfuncs for very simple expressions.  "Starting up"
	 * the full interpreter is a measurable overhead for these, and these
	 * patterns occur often enough to be worth optimizing.
	 */
	if (state->steps_len == 3)
	{
		ExprEvalOp	step0 = state->steps[0].opcode;
		ExprEvalOp	step1 = state->steps[1].opcode;

		if (step0 == EEOP_INNER_FETCHSOME &&
			step1 == EEOP_INNER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustInnerVar;
			return;
		}
		else if (step0 == EEOP_OUTER_FETCHSOME &&
				 step1 == EEOP_OUTER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustOuterVar;
			return;
		}
		else if (step0 == EEOP_SCAN_FETCHSOME &&
				 step1 == EEOP_SCAN_VAR)
		{
			state->evalfunc_private = (void *) ExecJustScanVar;
			return;
		}
		else if (step0 == EEOP_INNER_FETCHSOME &&
				 step1 == EEOP_ASSIGN_INNER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustAssignInnerVar;
			return;
		}
		else if (step0 == EEOP_OUTER_FETCHSOME &&
				 step1 == EEOP_ASSIGN_OUTER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustAssignOuterVar;
			return;
		}
		else if (step0 == EEOP_SCAN_FETCHSOME &&
				 step1 == EEOP_ASSIGN_SCAN_VAR)
		{
			state->evalfunc_private = (void *) ExecJustAssignScanVar;
			return;
		}
		else if (step0 == EEOP_CASE_TESTVAL &&
				 step1 == EEOP_FUNCEXPR_STRICT &&
				 state->steps[0].d.casetest.value)
		{
			state->evalfunc_private = (void *) ExecJustApplyFuncToCase;
			return;
		}
	}
	else if (state->steps_len == 2)
	{
		ExprEvalOp	step0 = state->steps[0].opcode;

		if (step0 == EEOP_CONST)
		{
			state->evalfunc_private = (void *) ExecJustConst;
			return;
		}
		else if (step0 == EEOP_INNER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustInnerVarVirt;
			return;
		}
		else if (step0 == EEOP_OUTER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustOuterVarVirt;
			return;
		}
		else if (step0 == EEOP_SCAN_VAR)
		{
			state->evalfunc_private = (void *) ExecJustScanVarVirt;
			return;
		}
		else if (step0 == EEOP_ASSIGN_INNER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustAssignInnerVarVirt;
			return;
		}
		else if (step0 == EEOP_ASSIGN_OUTER_VAR)
		{
			state->evalfunc_private = (void *) ExecJustAssignOuterVarVirt;
			return;
		}
		else if (step0 == EEOP_ASSIGN_SCAN_VAR)
		{
			state->evalfunc_private = (void *) ExecJustAssignScanVarVirt;
			return;
		}
	}

#if defined(EEO_USE_COMPUTED_GOTO)

	/*
	 * In the direct-threaded implementation, replace each opcode with the
	 * address to jump to.  (Use ExecEvalStepOp() to get back the opcode.)
	 */
	{
		int			off;

		for (off = 0; off < state->steps_len; off++)
		{
			ExprEvalStep *op = &state->steps[off];

			op->opcode = EEO_OPCODE(op->opcode);
		}

		state->flags |= EEO_FLAG_DIRECT_THREADED;
	}
#endif							/* EEO_USE_COMPUTED_GOTO */

	state->evalfunc_private = (void *) ExecInterpExpr;
}