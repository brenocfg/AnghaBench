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
typedef  int int32 ;

/* Variables and functions */

char *
pg_ltostr(char *str, int32 value)
{
	char	   *start;
	char	   *end;

	/*
	 * Handle negative numbers in a special way.  We can't just write a '-'
	 * prefix and reverse the sign as that would overflow for INT32_MIN.
	 */
	if (value < 0)
	{
		*str++ = '-';

		/* Mark the position we must reverse the string from. */
		start = str;

		/* Compute the result string backwards. */
		do
		{
			int32		oldval = value;
			int32		remainder;

			value /= 10;
			remainder = oldval - value * 10;
			/* As above, we expect remainder to be negative. */
			*str++ = '0' - remainder;
		} while (value != 0);
	}
	else
	{
		/* Mark the position we must reverse the string from. */
		start = str;

		/* Compute the result string backwards. */
		do
		{
			int32		oldval = value;
			int32		remainder;

			value /= 10;
			remainder = oldval - value * 10;
			*str++ = '0' + remainder;
		} while (value != 0);
	}

	/* Remember the end+1 and back up 'str' to the last character. */
	end = str--;

	/* Reverse string. */
	while (start < str)
	{
		char		swap = *start;

		*start++ = *str;
		*str-- = swap;
	}

	return end;
}