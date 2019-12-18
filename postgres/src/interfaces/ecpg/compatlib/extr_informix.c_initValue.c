#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long val; char sign; int maxdigits; int digits; int remaining; char* val_string; } ;

/* Variables and functions */
 int LONG_MAX ; 
 int log10 (int) ; 
 scalar_t__ malloc (int) ; 
 TYPE_1__ value ; 

__attribute__((used)) static int
initValue(long lng_val)
{
	int			i,
				j;
	long		l,
				dig;

	/* set some obvious things */
	value.val = lng_val >= 0 ? lng_val : lng_val * (-1);
	value.sign = lng_val >= 0 ? '+' : '-';
	value.maxdigits = log10(2) * (8 * sizeof(long) - 1);

	/* determine the number of digits */
	i = 0;
	l = 1;
	do
	{
		i++;
		l *= 10;
	}
	while ((l - 1) < value.val && l <= LONG_MAX / 10);

	if (l <= LONG_MAX / 10)
	{
		value.digits = i;
		l /= 10;
	}
	else
		value.digits = i + 1;

	value.remaining = value.digits;

	/* convert the long to string */
	if ((value.val_string = (char *) malloc(value.digits + 1)) == NULL)
		return -1;
	dig = value.val;
	for (i = value.digits, j = 0; i > 0; i--, j++)
	{
		value.val_string[j] = dig / l + '0';
		dig = dig % l;
		l /= 10;
	}
	value.val_string[value.digits] = '\0';
	return 0;
}