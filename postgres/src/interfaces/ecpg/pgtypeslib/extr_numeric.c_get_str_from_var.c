#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sign; int weight; int ndigits; int* digits; } ;
typedef  TYPE_1__ numeric ;

/* Variables and functions */
 int Max (int,int) ; 
 int Min (int,int) ; 
 scalar_t__ NUMERIC_NAN ; 
 scalar_t__ NUMERIC_NEG ; 
 scalar_t__ pgtypes_alloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static char *
get_str_from_var(numeric *var, int dscale)
{
	char	   *str;
	char	   *cp;
	int			i;
	int			d;

	if (var->sign == NUMERIC_NAN)
	{
		str = (char *) pgtypes_alloc(4);
		if (str == NULL)
			return NULL;
		sprintf(str, "NaN");
		return str;
	}

	/*
	 * Check if we must round up before printing the value and do so.
	 */
	i = dscale + var->weight + 1;
	if (i >= 0 && var->ndigits > i)
	{
		int			carry = (var->digits[i] > 4) ? 1 : 0;

		var->ndigits = i;

		while (carry)
		{
			carry += var->digits[--i];
			var->digits[i] = carry % 10;
			carry /= 10;
		}

		if (i < 0)
		{
			var->digits--;
			var->ndigits++;
			var->weight++;
		}
	}
	else
		var->ndigits = Max(0, Min(i, var->ndigits));

	/*
	 * Allocate space for the result
	 */
	if ((str = (char *) pgtypes_alloc(Max(0, dscale) + Max(0, var->weight) + 4)) == NULL)
		return NULL;
	cp = str;

	/*
	 * Output a dash for negative values
	 */
	if (var->sign == NUMERIC_NEG)
		*cp++ = '-';

	/*
	 * Output all digits before the decimal point
	 */
	i = Max(var->weight, 0);
	d = 0;

	while (i >= 0)
	{
		if (i <= var->weight && d < var->ndigits)
			*cp++ = var->digits[d++] + '0';
		else
			*cp++ = '0';
		i--;
	}

	/*
	 * If requested, output a decimal point and all the digits that follow it.
	 */
	if (dscale > 0)
	{
		*cp++ = '.';
		while (i >= -dscale)
		{
			if (i <= var->weight && d < var->ndigits)
				*cp++ = var->digits[d++] + '0';
			else
				*cp++ = '0';
			i--;
		}
	}

	/*
	 * terminate the string and return it
	 */
	*cp = '\0';
	return str;
}