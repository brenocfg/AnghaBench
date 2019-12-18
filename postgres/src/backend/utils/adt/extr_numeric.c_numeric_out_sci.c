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
 char* get_str_from_var_sci (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_var_from_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pstrdup (char*) ; 

char *
numeric_out_sci(Numeric num, int scale)
{
	NumericVar	x;
	char	   *str;

	/*
	 * Handle NaN
	 */
	if (NUMERIC_IS_NAN(num))
		return pstrdup("NaN");

	init_var_from_num(num, &x);

	str = get_str_from_var_sci(&x, scale);

	return str;
}