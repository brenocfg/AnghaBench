#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int dscale; scalar_t__ ndigits; int weight; } ;
typedef  TYPE_1__ NumericVar ;

/* Variables and functions */
 double Abs (double) ; 
 int DEC_DIGITS ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int Max (int,int /*<<< orphan*/ ) ; 
 int NUMERIC_MAX_RESULT_SCALE ; 
 int /*<<< orphan*/  NUMERIC_MIN_DISPLAY_SCALE ; 
 int /*<<< orphan*/  add_var (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__ const_one ; 
 TYPE_1__ const const_two ; 
 int /*<<< orphan*/  div_var_fast (TYPE_1__*,TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  free_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__*) ; 
 int /*<<< orphan*/  mul_var (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 
 double numericvar_to_double_no_overflow (TYPE_1__*) ; 
 int /*<<< orphan*/  round_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_var_from_var (TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static void
exp_var(const NumericVar *arg, NumericVar *result, int rscale)
{
	NumericVar	x;
	NumericVar	elem;
	NumericVar	ni;
	double		val;
	int			dweight;
	int			ndiv2;
	int			sig_digits;
	int			local_rscale;

	init_var(&x);
	init_var(&elem);
	init_var(&ni);

	set_var_from_var(arg, &x);

	/*
	 * Estimate the dweight of the result using floating point arithmetic, so
	 * that we can choose an appropriate local rscale for the calculation.
	 */
	val = numericvar_to_double_no_overflow(&x);

	/* Guard against overflow */
	/* If you change this limit, see also power_var()'s limit */
	if (Abs(val) >= NUMERIC_MAX_RESULT_SCALE * 3)
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value overflows numeric format")));

	/* decimal weight = log10(e^x) = x * log10(e) */
	dweight = (int) (val * 0.434294481903252);

	/*
	 * Reduce x to the range -0.01 <= x <= 0.01 (approximately) by dividing by
	 * 2^n, to improve the convergence rate of the Taylor series.
	 */
	if (Abs(val) > 0.01)
	{
		NumericVar	tmp;

		init_var(&tmp);
		set_var_from_var(&const_two, &tmp);

		ndiv2 = 1;
		val /= 2;

		while (Abs(val) > 0.01)
		{
			ndiv2++;
			val /= 2;
			add_var(&tmp, &tmp, &tmp);
		}

		local_rscale = x.dscale + ndiv2;
		div_var_fast(&x, &tmp, &x, local_rscale, true);

		free_var(&tmp);
	}
	else
		ndiv2 = 0;

	/*
	 * Set the scale for the Taylor series expansion.  The final result has
	 * (dweight + rscale + 1) significant digits.  In addition, we have to
	 * raise the Taylor series result to the power 2^ndiv2, which introduces
	 * an error of up to around log10(2^ndiv2) digits, so work with this many
	 * extra digits of precision (plus a few more for good measure).
	 */
	sig_digits = 1 + dweight + rscale + (int) (ndiv2 * 0.301029995663981);
	sig_digits = Max(sig_digits, 0) + 8;

	local_rscale = sig_digits - 1;

	/*
	 * Use the Taylor series
	 *
	 * exp(x) = 1 + x + x^2/2! + x^3/3! + ...
	 *
	 * Given the limited range of x, this should converge reasonably quickly.
	 * We run the series until the terms fall below the local_rscale limit.
	 */
	add_var(&const_one, &x, result);

	mul_var(&x, &x, &elem, local_rscale);
	set_var_from_var(&const_two, &ni);
	div_var_fast(&elem, &ni, &elem, local_rscale, true);

	while (elem.ndigits != 0)
	{
		add_var(result, &elem, result);

		mul_var(&elem, &x, &elem, local_rscale);
		add_var(&ni, &const_one, &ni);
		div_var_fast(&elem, &ni, &elem, local_rscale, true);
	}

	/*
	 * Compensate for the argument range reduction.  Since the weight of the
	 * result doubles with each multiplication, we can reduce the local rscale
	 * as we proceed.
	 */
	while (ndiv2-- > 0)
	{
		local_rscale = sig_digits - result->weight * 2 * DEC_DIGITS;
		local_rscale = Max(local_rscale, NUMERIC_MIN_DISPLAY_SCALE);
		mul_var(result, result, result, local_rscale);
	}

	/* Round to requested rscale */
	round_var(result, rscale);

	free_var(&x);
	free_var(&elem);
	free_var(&ni);
}