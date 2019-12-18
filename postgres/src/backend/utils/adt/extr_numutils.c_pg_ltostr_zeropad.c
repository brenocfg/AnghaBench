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
typedef  size_t int32 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* pg_ltostr (char*,size_t) ; 

char *
pg_ltostr_zeropad(char *str, int32 value, int32 minwidth)
{
	char	   *start = str;
	char	   *end = &str[minwidth];
	int32		num = value;

	Assert(minwidth > 0);

	/*
	 * Handle negative numbers in a special way.  We can't just write a '-'
	 * prefix and reverse the sign as that would overflow for INT32_MIN.
	 */
	if (num < 0)
	{
		*start++ = '-';
		minwidth--;

		/*
		 * Build the number starting at the last digit.  Here remainder will
		 * be a negative number, so we must reverse the sign before adding '0'
		 * in order to get the correct ASCII digit.
		 */
		while (minwidth--)
		{
			int32		oldval = num;
			int32		remainder;

			num /= 10;
			remainder = oldval - num * 10;
			start[minwidth] = '0' - remainder;
		}
	}
	else
	{
		/* Build the number starting at the last digit */
		while (minwidth--)
		{
			int32		oldval = num;
			int32		remainder;

			num /= 10;
			remainder = oldval - num * 10;
			start[minwidth] = '0' + remainder;
		}
	}

	/*
	 * If minwidth was not high enough to fit the number then num won't have
	 * been divided down to zero.  We punt the problem to pg_ltostr(), which
	 * will generate a correct answer in the minimum valid width.
	 */
	if (num != 0)
		return pg_ltostr(str, value);

	/* Otherwise, return last output character + 1 */
	return end;
}