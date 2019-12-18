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
 int DIVISOR ; 
 char* _add (char*,char*,char const*) ; 
 char* _conv (int,char*,char*,char const*) ; 

__attribute__((used)) static char *
_yconv(int a, int b, bool convert_top, bool convert_yy,
	   char *pt, const char *ptlim)
{
	int			lead;
	int			trail;

#define DIVISOR	100
	trail = a % DIVISOR + b % DIVISOR;
	lead = a / DIVISOR + b / DIVISOR + trail / DIVISOR;
	trail %= DIVISOR;
	if (trail < 0 && lead > 0)
	{
		trail += DIVISOR;
		--lead;
	}
	else if (lead < 0 && trail > 0)
	{
		trail -= DIVISOR;
		++lead;
	}
	if (convert_top)
	{
		if (lead == 0 && trail < 0)
			pt = _add("-0", pt, ptlim);
		else
			pt = _conv(lead, "%02d", pt, ptlim);
	}
	if (convert_yy)
		pt = _conv(((trail < 0) ? -trail : trail), "%02d", pt, ptlim);
	return pt;
}