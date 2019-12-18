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
typedef  int fsec_t ;

/* Variables and functions */
 int Abs (int) ; 
 int /*<<< orphan*/  Assert (int) ; 
 char* pg_ltostr (char*,int) ; 
 char* pg_ltostr_zeropad (char*,int,int) ; 

__attribute__((used)) static char *
AppendSeconds(char *cp, int sec, fsec_t fsec, int precision, bool fillzeros)
{
	Assert(precision >= 0);

	if (fillzeros)
		cp = pg_ltostr_zeropad(cp, Abs(sec), 2);
	else
		cp = pg_ltostr(cp, Abs(sec));

	/* fsec_t is just an int32 */
	if (fsec != 0)
	{
		int32		value = Abs(fsec);
		char	   *end = &cp[precision + 1];
		bool		gotnonzero = false;

		*cp++ = '.';

		/*
		 * Append the fractional seconds part.  Note that we don't want any
		 * trailing zeros here, so since we're building the number in reverse
		 * we'll skip appending zeros until we've output a non-zero digit.
		 */
		while (precision--)
		{
			int32		oldval = value;
			int32		remainder;

			value /= 10;
			remainder = oldval - value * 10;

			/* check if we got a non-zero */
			if (remainder)
				gotnonzero = true;

			if (gotnonzero)
				cp[precision] = '0' + remainder;
			else
				end = &cp[precision];
		}

		/*
		 * If we still have a non-zero value then precision must have not been
		 * enough to print the number.  We punt the problem to pg_ltostr(),
		 * which will generate a correct answer in the minimum valid width.
		 */
		if (value)
			return pg_ltostr(cp, Abs(fsec));

		return end;
	}
	else
		return cp;
}