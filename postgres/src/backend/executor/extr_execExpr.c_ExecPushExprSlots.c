#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ last_var; int fixed; int /*<<< orphan*/ * known_desc; int /*<<< orphan*/ * kind; } ;
struct TYPE_9__ {TYPE_1__ fetch; } ;
struct TYPE_11__ {TYPE_2__ d; int /*<<< orphan*/  opcode; int /*<<< orphan*/ * resnull; int /*<<< orphan*/ * resvalue; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__ last_inner; scalar_t__ last_outer; scalar_t__ last_scan; } ;
typedef  TYPE_3__ LastAttnumInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_4__ ExprEvalStep ;

/* Variables and functions */
 int /*<<< orphan*/  EEOP_INNER_FETCHSOME ; 
 int /*<<< orphan*/  EEOP_OUTER_FETCHSOME ; 
 int /*<<< orphan*/  EEOP_SCAN_FETCHSOME ; 
 scalar_t__ ExecComputeSlotInfo (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ExprEvalPushStep (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void
ExecPushExprSlots(ExprState *state, LastAttnumInfo *info)
{
	ExprEvalStep scratch = {0};

	scratch.resvalue = NULL;
	scratch.resnull = NULL;

	/* Emit steps as needed */
	if (info->last_inner > 0)
	{
		scratch.opcode = EEOP_INNER_FETCHSOME;
		scratch.d.fetch.last_var = info->last_inner;
		scratch.d.fetch.fixed = false;
		scratch.d.fetch.kind = NULL;
		scratch.d.fetch.known_desc = NULL;
		if (ExecComputeSlotInfo(state, &scratch))
			ExprEvalPushStep(state, &scratch);
	}
	if (info->last_outer > 0)
	{
		scratch.opcode = EEOP_OUTER_FETCHSOME;
		scratch.d.fetch.last_var = info->last_outer;
		scratch.d.fetch.fixed = false;
		scratch.d.fetch.kind = NULL;
		scratch.d.fetch.known_desc = NULL;
		if (ExecComputeSlotInfo(state, &scratch))
			ExprEvalPushStep(state, &scratch);
	}
	if (info->last_scan > 0)
	{
		scratch.opcode = EEOP_SCAN_FETCHSOME;
		scratch.d.fetch.last_var = info->last_scan;
		scratch.d.fetch.fixed = false;
		scratch.d.fetch.kind = NULL;
		scratch.d.fetch.known_desc = NULL;
		if (ExecComputeSlotInfo(state, &scratch))
			ExprEvalPushStep(state, &scratch);
	}
}