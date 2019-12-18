#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int weight; scalar_t__ ndigits; } ;
typedef  TYPE_1__ const NumericVar ;

/* Variables and functions */
 int DEC_DIGITS ; 
 int /*<<< orphan*/  ERRCODE_INVALID_ARGUMENT_FOR_LOG ; 
 int /*<<< orphan*/  ERROR ; 
 int Max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_MIN_DISPLAY_SCALE ; 
 int /*<<< orphan*/  add_var (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int cmp_var (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ const const_one ; 
 int /*<<< orphan*/  const_one_point_one ; 
 TYPE_1__ const const_two ; 
 int /*<<< orphan*/  const_zero ; 
 int /*<<< orphan*/  const_zero_point_nine ; 
 int /*<<< orphan*/  div_var_fast (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  free_var (TYPE_1__ const*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mul_var (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  set_var_from_var (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  sqrt_var (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  sub_var (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 

__attribute__((used)) static void
ln_var(const NumericVar *arg, NumericVar *result, int rscale)
{
	NumericVar	x;
	NumericVar	xx;
	NumericVar	ni;
	NumericVar	elem;
	NumericVar	fact;
	int			local_rscale;
	int			cmp;

	cmp = cmp_var(arg, &const_zero);
	if (cmp == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_LOG),
				 errmsg("cannot take logarithm of zero")));
	else if (cmp < 0)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_ARGUMENT_FOR_LOG),
				 errmsg("cannot take logarithm of a negative number")));

	init_var(&x);
	init_var(&xx);
	init_var(&ni);
	init_var(&elem);
	init_var(&fact);

	set_var_from_var(arg, &x);
	set_var_from_var(&const_two, &fact);

	/*
	 * Reduce input into range 0.9 < x < 1.1 with repeated sqrt() operations.
	 *
	 * The final logarithm will have up to around rscale+6 significant digits.
	 * Each sqrt() will roughly halve the weight of x, so adjust the local
	 * rscale as we work so that we keep this many significant digits at each
	 * step (plus a few more for good measure).
	 */
	while (cmp_var(&x, &const_zero_point_nine) <= 0)
	{
		local_rscale = rscale - x.weight * DEC_DIGITS / 2 + 8;
		local_rscale = Max(local_rscale, NUMERIC_MIN_DISPLAY_SCALE);
		sqrt_var(&x, &x, local_rscale);
		mul_var(&fact, &const_two, &fact, 0);
	}
	while (cmp_var(&x, &const_one_point_one) >= 0)
	{
		local_rscale = rscale - x.weight * DEC_DIGITS / 2 + 8;
		local_rscale = Max(local_rscale, NUMERIC_MIN_DISPLAY_SCALE);
		sqrt_var(&x, &x, local_rscale);
		mul_var(&fact, &const_two, &fact, 0);
	}

	/*
	 * We use the Taylor series for 0.5 * ln((1+z)/(1-z)),
	 *
	 * z + z^3/3 + z^5/5 + ...
	 *
	 * where z = (x-1)/(x+1) is in the range (approximately) -0.053 .. 0.048
	 * due to the above range-reduction of x.
	 *
	 * The convergence of this is not as fast as one would like, but is
	 * tolerable given that z is small.
	 */
	local_rscale = rscale + 8;

	sub_var(&x, &const_one, result);
	add_var(&x, &const_one, &elem);
	div_var_fast(result, &elem, result, local_rscale, true);
	set_var_from_var(result, &xx);
	mul_var(result, result, &x, local_rscale);

	set_var_from_var(&const_one, &ni);

	for (;;)
	{
		add_var(&ni, &const_two, &ni);
		mul_var(&xx, &x, &xx, local_rscale);
		div_var_fast(&xx, &ni, &elem, local_rscale, true);

		if (elem.ndigits == 0)
			break;

		add_var(result, &elem, result);

		if (elem.weight < (result->weight - local_rscale * 2 / DEC_DIGITS))
			break;
	}

	/* Compensate for argument range reduction, round to requested rscale */
	mul_var(result, &fact, result, rscale);

	free_var(&x);
	free_var(&xx);
	free_var(&ni);
	free_var(&elem);
	free_var(&fact);
}