#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const TupleTableSlotOps ;
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_14__ {int fixed; int /*<<< orphan*/  const* kind; int /*<<< orphan*/ * known_desc; } ;
struct TYPE_15__ {TYPE_1__ fetch; } ;
struct TYPE_18__ {scalar_t__ opcode; TYPE_2__ d; } ;
struct TYPE_17__ {TYPE_3__* parent; } ;
struct TYPE_16__ {int scanopsfixed; scalar_t__ scanopsset; int /*<<< orphan*/  const* scanops; int /*<<< orphan*/ * scandesc; int /*<<< orphan*/  const* outerops; scalar_t__ outeropsset; int /*<<< orphan*/  outeropsfixed; int /*<<< orphan*/  const* innerops; scalar_t__ inneropsset; int /*<<< orphan*/  inneropsfixed; } ;
typedef  TYPE_3__ PlanState ;
typedef  TYPE_4__ ExprState ;
typedef  TYPE_5__ ExprEvalStep ;
typedef  scalar_t__ ExprEvalOp ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EEOP_INNER_FETCHSOME ; 
 scalar_t__ EEOP_OUTER_FETCHSOME ; 
 scalar_t__ EEOP_SCAN_FETCHSOME ; 
 int /*<<< orphan*/  const* ExecGetResultSlotOps (TYPE_3__*,int*) ; 
 int /*<<< orphan*/ * ExecGetResultType (TYPE_3__*) ; 
 int /*<<< orphan*/  const TTSOpsVirtual ; 
 TYPE_3__* innerPlanState (TYPE_3__*) ; 
 TYPE_3__* outerPlanState (TYPE_3__*) ; 

__attribute__((used)) static bool
ExecComputeSlotInfo(ExprState *state, ExprEvalStep *op)
{
	PlanState  *parent = state->parent;
	TupleDesc	desc = NULL;
	const TupleTableSlotOps *tts_ops = NULL;
	bool		isfixed = false;
	ExprEvalOp	opcode = op->opcode;

	Assert(opcode == EEOP_INNER_FETCHSOME ||
		   opcode == EEOP_OUTER_FETCHSOME ||
		   opcode == EEOP_SCAN_FETCHSOME);

	if (op->d.fetch.known_desc != NULL)
	{
		desc = op->d.fetch.known_desc;
		tts_ops = op->d.fetch.kind;
		isfixed = op->d.fetch.kind != NULL;
	}
	else if (!parent)
	{
		isfixed = false;
	}
	else if (opcode == EEOP_INNER_FETCHSOME)
	{
		PlanState  *is = innerPlanState(parent);

		if (parent->inneropsset && !parent->inneropsfixed)
		{
			isfixed = false;
		}
		else if (parent->inneropsset && parent->innerops)
		{
			isfixed = true;
			tts_ops = parent->innerops;
			desc = ExecGetResultType(is);
		}
		else if (is)
		{
			tts_ops = ExecGetResultSlotOps(is, &isfixed);
			desc = ExecGetResultType(is);
		}
	}
	else if (opcode == EEOP_OUTER_FETCHSOME)
	{
		PlanState  *os = outerPlanState(parent);

		if (parent->outeropsset && !parent->outeropsfixed)
		{
			isfixed = false;
		}
		else if (parent->outeropsset && parent->outerops)
		{
			isfixed = true;
			tts_ops = parent->outerops;
			desc = ExecGetResultType(os);
		}
		else if (os)
		{
			tts_ops = ExecGetResultSlotOps(os, &isfixed);
			desc = ExecGetResultType(os);
		}
	}
	else if (opcode == EEOP_SCAN_FETCHSOME)
	{
		desc = parent->scandesc;

		if (parent && parent->scanops)
			tts_ops = parent->scanops;

		if (parent->scanopsset)
			isfixed = parent->scanopsfixed;
	}

	if (isfixed && desc != NULL && tts_ops != NULL)
	{
		op->d.fetch.fixed = true;
		op->d.fetch.kind = tts_ops;
		op->d.fetch.known_desc = desc;
	}
	else
	{
		op->d.fetch.fixed = false;
		op->d.fetch.kind = NULL;
		op->d.fetch.known_desc = NULL;
	}

	/* if the slot is known to always virtual we never need to deform */
	if (op->d.fetch.fixed && op->d.fetch.kind == &TTSOpsVirtual)
		return false;

	return true;
}