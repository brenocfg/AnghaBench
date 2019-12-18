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
 int PG_INT32_MIN ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

void
pg_ltoa(int32 value, char *a)
{
	char	   *start = a;
	bool		neg = false;

	/*
	 * Avoid problems with the most negative integer not being representable
	 * as a positive integer.
	 */
	if (value == PG_INT32_MIN)
	{
		memcpy(a, "-2147483648", 12);
		return;
	}
	else if (value < 0)
	{
		value = -value;
		neg = true;
	}

	/* Compute the result string backwards. */
	do
	{
		int32		remainder;
		int32		oldval = value;

		value /= 10;
		remainder = oldval - value * 10;
		*a++ = '0' + remainder;
	} while (value != 0);

	if (neg)
		*a++ = '-';

	/* Add trailing NUL byte, and back up 'a' to the last character. */
	*a-- = '\0';

	/* Reverse string. */
	while (start < a)
	{
		char		swap = *start;

		*start++ = *a;
		*a-- = swap;
	}
}