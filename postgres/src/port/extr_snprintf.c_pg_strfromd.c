#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* bufstart; char* bufptr; char* bufend; int nchars; int failed; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ PrintfTarget ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  dopr_outch (int,TYPE_1__*) ; 
 int /*<<< orphan*/  dostr (char*,int,TYPE_1__*) ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 scalar_t__ memcmp (double*,double const*,int) ; 
 int sprintf (char*,char*,int,double) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
pg_strfromd(char *str, size_t count, int precision, double value)
{
	PrintfTarget target;
	int			signvalue = 0;
	int			vallen;
	char		fmt[8];
	char		convert[64];

	/* Set up the target like pg_snprintf, but require nonempty buffer */
	Assert(count > 0);
	target.bufstart = target.bufptr = str;
	target.bufend = str + count - 1;
	target.stream = NULL;
	target.nchars = 0;
	target.failed = false;

	/*
	 * We bound precision to a reasonable range; the combination of this and
	 * the knowledge that we're using "g" format without padding allows the
	 * convert[] buffer to be reasonably small.
	 */
	if (precision < 1)
		precision = 1;
	else if (precision > 32)
		precision = 32;

	/*
	 * The rest is just an inlined version of the fmtfloat() logic above,
	 * simplified using the knowledge that no padding is wanted.
	 */
	if (isnan(value))
	{
		strcpy(convert, "NaN");
		vallen = 3;
	}
	else
	{
		static const double dzero = 0.0;

		if (value < 0.0 ||
			(value == 0.0 &&
			 memcmp(&value, &dzero, sizeof(double)) != 0))
		{
			signvalue = '-';
			value = -value;
		}

		if (isinf(value))
		{
			strcpy(convert, "Infinity");
			vallen = 8;
		}
		else
		{
			fmt[0] = '%';
			fmt[1] = '.';
			fmt[2] = '*';
			fmt[3] = 'g';
			fmt[4] = '\0';
			vallen = sprintf(convert, fmt, precision, value);
			if (vallen < 0)
			{
				target.failed = true;
				goto fail;
			}

#ifdef WIN32
			if (vallen >= 6 &&
				convert[vallen - 5] == 'e' &&
				convert[vallen - 3] == '0')
			{
				convert[vallen - 3] = convert[vallen - 2];
				convert[vallen - 2] = convert[vallen - 1];
				vallen--;
			}
#endif
		}
	}

	if (signvalue)
		dopr_outch(signvalue, &target);

	dostr(convert, vallen, &target);

fail:
	*(target.bufptr) = '\0';
	return target.failed ? -1 : (target.bufptr - target.bufstart
								 + target.nchars);
}