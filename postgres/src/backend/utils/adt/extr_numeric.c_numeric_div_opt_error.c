#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ndigits; scalar_t__* digits; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int /*<<< orphan*/ * Numeric ;

/* Variables and functions */
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const_nan ; 
 int /*<<< orphan*/  div_var (TYPE_1__*,TYPE_1__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  free_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * make_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_result_opt_error (TYPE_1__*,int*) ; 
 int select_div_scale (TYPE_1__*,TYPE_1__*) ; 

Numeric
numeric_div_opt_error(Numeric num1, Numeric num2, bool *have_error)
{
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;
	int			rscale;

	if (have_error)
		*have_error = false;

	/*
	 * Handle NaN
	 */
	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return make_result(&const_nan);

	/*
	 * Unpack the arguments
	 */
	init_var_from_num(num1, &arg1);
	init_var_from_num(num2, &arg2);

	init_var(&result);

	/*
	 * Select scale for division result
	 */
	rscale = select_div_scale(&arg1, &arg2);

	/*
	 * If "have_error" is provided, check for division by zero here
	 */
	if (have_error && (arg2.ndigits == 0 || arg2.digits[0] == 0))
	{
		*have_error = true;
		return NULL;
	}

	/*
	 * Do the divide and return the result
	 */
	div_var(&arg1, &arg2, &result, rscale, true);

	res = make_result_opt_error(&result, have_error);

	free_var(&result);

	return res;
}