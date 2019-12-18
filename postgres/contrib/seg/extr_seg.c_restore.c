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
 int Abs (int) ; 
 int /*<<< orphan*/  FLT_DIG ; 
 int Min (int,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
restore(char *result, float val, int n)
{
	char		buf[25] = {
		'0', '0', '0', '0', '0',
		'0', '0', '0', '0', '0',
		'0', '0', '0', '0', '0',
		'0', '0', '0', '0', '0',
		'0', '0', '0', '0', '\0'
	};
	char	   *p;
	int			exp;
	int			i,
				dp,
				sign;

	/*
	 * Put a cap on the number of significant digits to avoid garbage in the
	 * output and ensure we don't overrun the result buffer.
	 */
	n = Min(n, FLT_DIG);

	/* remember the sign */
	sign = (val < 0 ? 1 : 0);

	/* print, in %e style to start with */
	sprintf(result, "%.*e", n - 1, val);

	/* find the exponent */
	p = strchr(result, 'e');

	/* punt if we have 'inf' or similar */
	if (p == NULL)
		return strlen(result);

	exp = atoi(p + 1);
	if (exp == 0)
	{
		/* just truncate off the 'e+00' */
		*p = '\0';
	}
	else
	{
		if (Abs(exp) <= 4)
		{
			/*
			 * remove the decimal point from the mantissa and write the digits
			 * to the buf array
			 */
			for (p = result + sign, i = 10, dp = 0; *p != 'e'; p++, i++)
			{
				buf[i] = *p;
				if (*p == '.')
				{
					dp = i--;	/* skip the decimal point */
				}
			}
			if (dp == 0)
				dp = i--;		/* no decimal point was found in the above
								 * for() loop */

			if (exp > 0)
			{
				if (dp - 10 + exp >= n)
				{
					/*
					 * the decimal point is behind the last significant digit;
					 * the digits in between must be converted to the exponent
					 * and the decimal point placed after the first digit
					 */
					exp = dp - 10 + exp - n;
					buf[10 + n] = '\0';

					/* insert the decimal point */
					if (n > 1)
					{
						dp = 11;
						for (i = 23; i > dp; i--)
							buf[i] = buf[i - 1];
						buf[dp] = '.';
					}

					/*
					 * adjust the exponent by the number of digits after the
					 * decimal point
					 */
					if (n > 1)
						sprintf(&buf[11 + n], "e%d", exp + n - 1);
					else
						sprintf(&buf[11], "e%d", exp + n - 1);

					if (sign)
					{
						buf[9] = '-';
						strcpy(result, &buf[9]);
					}
					else
						strcpy(result, &buf[10]);
				}
				else
				{				/* insert the decimal point */
					dp += exp;
					for (i = 23; i > dp; i--)
						buf[i] = buf[i - 1];
					buf[11 + n] = '\0';
					buf[dp] = '.';
					if (sign)
					{
						buf[9] = '-';
						strcpy(result, &buf[9]);
					}
					else
						strcpy(result, &buf[10]);
				}
			}
			else
			{					/* exp <= 0 */
				dp += exp - 1;
				buf[10 + n] = '\0';
				buf[dp] = '.';
				if (sign)
				{
					buf[dp - 2] = '-';
					strcpy(result, &buf[dp - 2]);
				}
				else
					strcpy(result, &buf[dp - 1]);
			}
		}

		/* do nothing for Abs(exp) > 4; %e must be OK */
		/* just get rid of zeroes after [eE]- and +zeroes after [Ee]. */

		/* ... this is not done yet. */
	}
	return strlen(result);
}