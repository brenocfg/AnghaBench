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

/* Variables and functions */
 int DBL_DIG ; 
 int /*<<< orphan*/  double_to_shortest_decimal_buf (double,char*) ; 
 int extra_float_digits ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pg_strfromd (char*,int,int,double) ; 

char *
float8out_internal(double num)
{
	char	   *ascii = (char *) palloc(32);
	int			ndig = DBL_DIG + extra_float_digits;

	if (extra_float_digits > 0)
	{
		double_to_shortest_decimal_buf(num, ascii);
		return ascii;
	}

	(void) pg_strfromd(ascii, 32, ndig, num);
	return ascii;
}