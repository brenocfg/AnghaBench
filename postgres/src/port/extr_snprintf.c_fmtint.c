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
typedef  int /*<<< orphan*/  convert ;
typedef  int /*<<< orphan*/  PrintfTarget ;

/* Variables and functions */
 int Max (int /*<<< orphan*/ ,int) ; 
 scalar_t__ adjust_sign (int,int,int*) ; 
 int compute_padlen (int,int,int) ; 
 int /*<<< orphan*/  dopr_outchmulti (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dostr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leading_pad (int,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trailing_pad (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fmtint(long long value, char type, int forcesign, int leftjust,
	   int minlen, int zpad, int precision, int pointflag,
	   PrintfTarget *target)
{
	unsigned long long base;
	unsigned long long uvalue;
	int			dosign;
	const char *cvt = "0123456789abcdef";
	int			signvalue = 0;
	char		convert[64];
	int			vallen = 0;
	int			padlen;			/* amount to pad */
	int			zeropad;		/* extra leading zeroes */

	switch (type)
	{
		case 'd':
		case 'i':
			base = 10;
			dosign = 1;
			break;
		case 'o':
			base = 8;
			dosign = 0;
			break;
		case 'u':
			base = 10;
			dosign = 0;
			break;
		case 'x':
			base = 16;
			dosign = 0;
			break;
		case 'X':
			cvt = "0123456789ABCDEF";
			base = 16;
			dosign = 0;
			break;
		default:
			return;				/* keep compiler quiet */
	}

	/* disable MSVC warning about applying unary minus to an unsigned value */
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146)
#endif
	/* Handle +/- */
	if (dosign && adjust_sign((value < 0), forcesign, &signvalue))
		uvalue = -(unsigned long long) value;
	else
		uvalue = (unsigned long long) value;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

	/*
	 * SUS: the result of converting 0 with an explicit precision of 0 is no
	 * characters
	 */
	if (value == 0 && pointflag && precision == 0)
		vallen = 0;
	else
	{
		/* make integer string */
		do
		{
			convert[sizeof(convert) - (++vallen)] = cvt[uvalue % base];
			uvalue = uvalue / base;
		} while (uvalue);
	}

	zeropad = Max(0, precision - vallen);

	padlen = compute_padlen(minlen, vallen + zeropad, leftjust);

	leading_pad(zpad, signvalue, &padlen, target);

	if (zeropad > 0)
		dopr_outchmulti('0', zeropad, target);

	dostr(convert + sizeof(convert) - vallen, vallen, target);

	trailing_pad(padlen, target);
}