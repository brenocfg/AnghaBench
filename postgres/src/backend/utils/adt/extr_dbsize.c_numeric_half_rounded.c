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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int) ; 
 int /*<<< orphan*/  NumericGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int8_numeric ; 
 int /*<<< orphan*/  numeric_add ; 
 int /*<<< orphan*/  numeric_div_trunc ; 
 int /*<<< orphan*/  numeric_ge ; 
 int /*<<< orphan*/  numeric_sub ; 

__attribute__((used)) static Numeric
numeric_half_rounded(Numeric n)
{
	Datum		d = NumericGetDatum(n);
	Datum		zero;
	Datum		one;
	Datum		two;
	Datum		result;

	zero = DirectFunctionCall1(int8_numeric, Int64GetDatum(0));
	one = DirectFunctionCall1(int8_numeric, Int64GetDatum(1));
	two = DirectFunctionCall1(int8_numeric, Int64GetDatum(2));

	if (DatumGetBool(DirectFunctionCall2(numeric_ge, d, zero)))
		d = DirectFunctionCall2(numeric_add, d, one);
	else
		d = DirectFunctionCall2(numeric_sub, d, one);

	result = DirectFunctionCall2(numeric_div_trunc, d, two);
	return DatumGetNumeric(result);
}