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
struct TYPE_9__ {scalar_t__ ndigits; scalar_t__* digits; } ;
typedef  TYPE_1__ NumericVar ;
typedef  int /*<<< orphan*/ * Numeric ;

/* Variables and functions */
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const_nan ; 
 int /*<<< orphan*/  free_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var (TYPE_1__*) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * make_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_result_opt_error (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_var (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

Numeric
numeric_mod_opt_error(Numeric num1, Numeric num2, bool *have_error)
{
	Numeric		res;
	NumericVar	arg1;
	NumericVar	arg2;
	NumericVar	result;

	if (have_error)
		*have_error = false;

	if (NUMERIC_IS_NAN(num1) || NUMERIC_IS_NAN(num2))
		return make_result(&const_nan);

	init_var_from_num(num1, &arg1);
	init_var_from_num(num2, &arg2);

	init_var(&result);

	/*
	 * If "have_error" is provided, check for division by zero here
	 */
	if (have_error && (arg2.ndigits == 0 || arg2.digits[0] == 0))
	{
		*have_error = true;
		return NULL;
	}

	mod_var(&arg1, &arg2, &result);

	res = make_result_opt_error(&result, NULL);

	free_var(&result);

	return res;
}