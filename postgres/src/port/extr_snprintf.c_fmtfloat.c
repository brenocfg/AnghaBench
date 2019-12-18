#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int failed; } ;
typedef  TYPE_1__ PrintfTarget ;

/* Variables and functions */
 int Min (int,int) ; 
 scalar_t__ adjust_sign (int,int,int*) ; 
 int compute_padlen (int,int,int) ; 
 int /*<<< orphan*/  dopr_outchmulti (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  dostr (char*,int,TYPE_1__*) ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  leading_pad (int,int,int*,TYPE_1__*) ; 
 scalar_t__ memcmp (double*,double const*,int) ; 
 int sprintf (char*,char*,double,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  trailing_pad (int,TYPE_1__*) ; 

__attribute__((used)) static void
fmtfloat(double value, char type, int forcesign, int leftjust,
		 int minlen, int zpad, int precision, int pointflag,
		 PrintfTarget *target)
{
	int			signvalue = 0;
	int			prec;
	int			vallen;
	char		fmt[8];
	char		convert[1024];
	int			zeropadlen = 0; /* amount to pad with zeroes */
	int			padlen;			/* amount to pad with spaces */

	/*
	 * We rely on the regular C library's sprintf to do the basic conversion,
	 * then handle padding considerations here.
	 *
	 * The dynamic range of "double" is about 1E+-308 for IEEE math, and not
	 * too wildly more than that with other hardware.  In "f" format, sprintf
	 * could therefore generate at most 308 characters to the left of the
	 * decimal point; while we need to allow the precision to get as high as
	 * 308+17 to ensure that we don't truncate significant digits from very
	 * small values.  To handle both these extremes, we use a buffer of 1024
	 * bytes and limit requested precision to 350 digits; this should prevent
	 * buffer overrun even with non-IEEE math.  If the original precision
	 * request was more than 350, separately pad with zeroes.
	 *
	 * We handle infinities and NaNs specially to ensure platform-independent
	 * output.
	 */
	if (precision < 0)			/* cover possible overflow of "accum" */
		precision = 0;
	prec = Min(precision, 350);

	if (isnan(value))
	{
		strcpy(convert, "NaN");
		vallen = 3;
		/* no zero padding, regardless of precision spec */
	}
	else
	{
		/*
		 * Handle sign (NaNs have no sign, so we don't do this in the case
		 * above).  "value < 0.0" will not be true for IEEE minus zero, so we
		 * detect that by looking for the case where value equals 0.0
		 * according to == but not according to memcmp.
		 */
		static const double dzero = 0.0;

		if (adjust_sign((value < 0.0 ||
						 (value == 0.0 &&
						  memcmp(&value, &dzero, sizeof(double)) != 0)),
						forcesign, &signvalue))
			value = -value;

		if (isinf(value))
		{
			strcpy(convert, "Infinity");
			vallen = 8;
			/* no zero padding, regardless of precision spec */
		}
		else if (pointflag)
		{
			zeropadlen = precision - prec;
			fmt[0] = '%';
			fmt[1] = '.';
			fmt[2] = '*';
			fmt[3] = type;
			fmt[4] = '\0';
			vallen = sprintf(convert, fmt, prec, value);
		}
		else
		{
			fmt[0] = '%';
			fmt[1] = type;
			fmt[2] = '\0';
			vallen = sprintf(convert, fmt, value);
		}
		if (vallen < 0)
			goto fail;

		/*
		 * Windows, alone among our supported platforms, likes to emit
		 * three-digit exponent fields even when two digits would do.  Hack
		 * such results to look like the way everyone else does it.
		 */
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

	padlen = compute_padlen(minlen, vallen + zeropadlen, leftjust);

	leading_pad(zpad, signvalue, &padlen, target);

	if (zeropadlen > 0)
	{
		/* If 'e' or 'E' format, inject zeroes before the exponent */
		char	   *epos = strrchr(convert, 'e');

		if (!epos)
			epos = strrchr(convert, 'E');
		if (epos)
		{
			/* pad before exponent */
			dostr(convert, epos - convert, target);
			if (zeropadlen > 0)
				dopr_outchmulti('0', zeropadlen, target);
			dostr(epos, vallen - (epos - convert), target);
		}
		else
		{
			/* no exponent, pad after the digits */
			dostr(convert, vallen, target);
			if (zeropadlen > 0)
				dopr_outchmulti('0', zeropadlen, target);
		}
	}
	else
	{
		/* no zero padding, just emit the number as-is */
		dostr(convert, vallen, target);
	}

	trailing_pad(padlen, target);
	return;

fail:
	target->failed = true;
}