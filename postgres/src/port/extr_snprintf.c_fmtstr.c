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
typedef  int /*<<< orphan*/  PrintfTarget ;

/* Variables and functions */
 int compute_padlen (int,int,int) ; 
 int /*<<< orphan*/  dopr_outchmulti (char,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dostr (char const*,int,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int strnlen (char const*,int) ; 
 int /*<<< orphan*/  trailing_pad (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fmtstr(const char *value, int leftjust, int minlen, int maxwidth,
	   int pointflag, PrintfTarget *target)
{
	int			padlen,
				vallen;			/* amount to pad */

	/*
	 * If a maxwidth (precision) is specified, we must not fetch more bytes
	 * than that.
	 */
	if (pointflag)
		vallen = strnlen(value, maxwidth);
	else
		vallen = strlen(value);

	padlen = compute_padlen(minlen, vallen, leftjust);

	if (padlen > 0)
	{
		dopr_outchmulti(' ', padlen, target);
		padlen = 0;
	}

	dostr(value, vallen, target);

	trailing_pad(padlen, target);
}