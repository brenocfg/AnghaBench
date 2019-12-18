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
 int /*<<< orphan*/  dopr_outch (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dopr_outchmulti (char,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
leading_pad(int zpad, int signvalue, int *padlen, PrintfTarget *target)
{
	int			maxpad;

	if (*padlen > 0 && zpad)
	{
		if (signvalue)
		{
			dopr_outch(signvalue, target);
			--(*padlen);
			signvalue = 0;
		}
		if (*padlen > 0)
		{
			dopr_outchmulti(zpad, *padlen, target);
			*padlen = 0;
		}
	}
	maxpad = (signvalue != 0);
	if (*padlen > maxpad)
	{
		dopr_outchmulti(' ', *padlen - maxpad, target);
		*padlen = maxpad;
	}
	if (signvalue)
	{
		dopr_outch(signvalue, target);
		if (*padlen > 0)
			--(*padlen);
		else if (*padlen < 0)
			++(*padlen);
	}
}