#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int maxScale; int maxScaleCount; int /*<<< orphan*/  sumX2; scalar_t__ calcSumX2; int /*<<< orphan*/  sumX; int /*<<< orphan*/  N; int /*<<< orphan*/  agg_context; int /*<<< orphan*/  NaNcount; } ;
struct TYPE_10__ {int dscale; } ;
typedef  TYPE_1__ NumericVar ;
typedef  TYPE_2__ NumericAggState ;
typedef  int /*<<< orphan*/  Numeric ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accum_sum_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mul_var (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
do_numeric_accum(NumericAggState *state, Numeric newval)
{
	NumericVar	X;
	NumericVar	X2;
	MemoryContext old_context;

	/* Count NaN inputs separately from all else */
	if (NUMERIC_IS_NAN(newval))
	{
		state->NaNcount++;
		return;
	}

	/* load processed number in short-lived context */
	init_var_from_num(newval, &X);

	/*
	 * Track the highest input dscale that we've seen, to support inverse
	 * transitions (see do_numeric_discard).
	 */
	if (X.dscale > state->maxScale)
	{
		state->maxScale = X.dscale;
		state->maxScaleCount = 1;
	}
	else if (X.dscale == state->maxScale)
		state->maxScaleCount++;

	/* if we need X^2, calculate that in short-lived context */
	if (state->calcSumX2)
	{
		init_var(&X2);
		mul_var(&X, &X, &X2, X.dscale * 2);
	}

	/* The rest of this needs to work in the aggregate context */
	old_context = MemoryContextSwitchTo(state->agg_context);

	state->N++;

	/* Accumulate sums */
	accum_sum_add(&(state->sumX), &X);

	if (state->calcSumX2)
		accum_sum_add(&(state->sumX2), &X2);

	MemoryContextSwitchTo(old_context);
}