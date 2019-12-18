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
typedef  int /*<<< orphan*/  Numeric ;

/* Variables and functions */
 int /*<<< orphan*/  NUMERIC_DIGITS (int /*<<< orphan*/ ) ; 
 scalar_t__ NUMERIC_IS_NAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_NDIGITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_SIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMERIC_WEIGHT (int /*<<< orphan*/ ) ; 
 int cmp_var_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmp_numerics(Numeric num1, Numeric num2)
{
	int			result;

	/*
	 * We consider all NANs to be equal and larger than any non-NAN. This is
	 * somewhat arbitrary; the important thing is to have a consistent sort
	 * order.
	 */
	if (NUMERIC_IS_NAN(num1))
	{
		if (NUMERIC_IS_NAN(num2))
			result = 0;			/* NAN = NAN */
		else
			result = 1;			/* NAN > non-NAN */
	}
	else if (NUMERIC_IS_NAN(num2))
	{
		result = -1;			/* non-NAN < NAN */
	}
	else
	{
		result = cmp_var_common(NUMERIC_DIGITS(num1), NUMERIC_NDIGITS(num1),
								NUMERIC_WEIGHT(num1), NUMERIC_SIGN(num1),
								NUMERIC_DIGITS(num2), NUMERIC_NDIGITS(num2),
								NUMERIC_WEIGHT(num2), NUMERIC_SIGN(num2));
	}

	return result;
}