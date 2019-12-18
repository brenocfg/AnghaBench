#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  NumericVar ;
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_var (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const_nan ; 
 int /*<<< orphan*/  free_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_result_opt_error (int /*<<< orphan*/ *,int*) ; 

Numeric
numeric_add_opt_error(Numeric num1, Numeric num2, bool *have_error)
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
	 * Unpack the values, let add_var() compute the result and return it.
	 */
	init_var_from_num(num1, &arg1);
	init_var_from_num(num2, &arg2);

	init_var(&result);
	add_var(&arg1, &arg2, &result);

	res = make_result_opt_error(&result, have_error);

	free_var(&result);

	return res;
}