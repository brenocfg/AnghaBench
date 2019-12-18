#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ N; scalar_t__ NaNcount; int /*<<< orphan*/  sumX2; int /*<<< orphan*/  sumX; } ;
struct TYPE_27__ {int dscale; } ;
typedef  TYPE_1__ const NumericVar ;
typedef  TYPE_2__ NumericAggState ;
typedef  int /*<<< orphan*/ * Numeric ;

/* Variables and functions */
 int /*<<< orphan*/  accum_sum_final (int /*<<< orphan*/ *,TYPE_1__ const*) ; 
 scalar_t__ cmp_var (TYPE_1__ const*,TYPE_1__ const*) ; 
 TYPE_1__ const const_nan ; 
 TYPE_1__ const const_one ; 
 TYPE_1__ const const_zero ; 
 int /*<<< orphan*/  div_var (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int,int) ; 
 int /*<<< orphan*/  free_var (TYPE_1__ const*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__ const*) ; 
 int /*<<< orphan*/  int64_to_numericvar (scalar_t__,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * make_result (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mul_var (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int select_div_scale (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  sqrt_var (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  sub_var (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static Numeric
numeric_stddev_internal(NumericAggState *state,
						bool variance, bool sample,
						bool *is_null)
{
	Numeric		res;
	NumericVar	vN,
				vsumX,
				vsumX2,
				vNminus1;
	const NumericVar *comp;
	int			rscale;

	/* Deal with empty input and NaN-input cases */
	if (state == NULL || (state->N + state->NaNcount) == 0)
	{
		*is_null = true;
		return NULL;
	}

	*is_null = false;

	if (state->NaNcount > 0)
		return make_result(&const_nan);

	init_var(&vN);
	init_var(&vsumX);
	init_var(&vsumX2);

	int64_to_numericvar(state->N, &vN);
	accum_sum_final(&(state->sumX), &vsumX);
	accum_sum_final(&(state->sumX2), &vsumX2);

	/*
	 * Sample stddev and variance are undefined when N <= 1; population stddev
	 * is undefined when N == 0. Return NULL in either case.
	 */
	if (sample)
		comp = &const_one;
	else
		comp = &const_zero;

	if (cmp_var(&vN, comp) <= 0)
	{
		*is_null = true;
		return NULL;
	}

	init_var(&vNminus1);
	sub_var(&vN, &const_one, &vNminus1);

	/* compute rscale for mul_var calls */
	rscale = vsumX.dscale * 2;

	mul_var(&vsumX, &vsumX, &vsumX, rscale);	/* vsumX = sumX * sumX */
	mul_var(&vN, &vsumX2, &vsumX2, rscale); /* vsumX2 = N * sumX2 */
	sub_var(&vsumX2, &vsumX, &vsumX2);	/* N * sumX2 - sumX * sumX */

	if (cmp_var(&vsumX2, &const_zero) <= 0)
	{
		/* Watch out for roundoff error producing a negative numerator */
		res = make_result(&const_zero);
	}
	else
	{
		if (sample)
			mul_var(&vN, &vNminus1, &vNminus1, 0);	/* N * (N - 1) */
		else
			mul_var(&vN, &vN, &vNminus1, 0);	/* N * N */
		rscale = select_div_scale(&vsumX2, &vNminus1);
		div_var(&vsumX2, &vNminus1, &vsumX, rscale, true);	/* variance */
		if (!variance)
			sqrt_var(&vsumX, &vsumX, rscale);	/* stddev */

		res = make_result(&vsumX);
	}

	free_var(&vNminus1);
	free_var(&vsumX);
	free_var(&vsumX2);

	return res;
}