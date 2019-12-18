#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dscale; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_nan ; 
 int /*<<< orphan*/  free_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  make_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_result_opt_error (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  mul_var (TYPE_1__*,TYPE_1__*,TYPE_1__*,scalar_t__) ; 

Numeric
numeric_mul_opt_error(Numeric num1, Numeric num2, bool *have_error)
{
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;
	Numeric		res;

	/*
	 * Handle NaN
	 */
	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return make_result(&const_nan);

	/*
	 * Unpack the values, let mul_var() compute the result and return it.
	 * Unlike add_var() and sub_var(), mul_var() will round its result. In the
	 * case of numeric_mul(), which is invoked for the * operator on numerics,
	 * we request exact representation for the product (rscale = sum(dscale of
	 * arg1, dscale of arg2)).
	 */
	init_var_from_num(num1, &arg1);
	init_var_from_num(num2, &arg2);

	init_var(&result);
	mul_var(&arg1, &arg2, &result, arg1.dscale + arg2.dscale);

	res = make_result_opt_error(&result, have_error);

	free_var(&result);

	return res;
}