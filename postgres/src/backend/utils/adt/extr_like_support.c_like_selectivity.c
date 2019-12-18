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
typedef  double Selectivity ;

/* Variables and functions */
 double ANY_CHAR_SEL ; 
 double FIXED_CHAR_SEL ; 
 double FULL_WILDCARD_SEL ; 

__attribute__((used)) static Selectivity
like_selectivity(const char *patt, int pattlen, bool case_insensitive)
{
	Selectivity sel = 1.0;
	int			pos;

	/* Skip any leading wildcard; it's already factored into initial sel */
	for (pos = 0; pos < pattlen; pos++)
	{
		if (patt[pos] != '%' && patt[pos] != '_')
			break;
	}

	for (; pos < pattlen; pos++)
	{
		/* % and _ are wildcard characters in LIKE */
		if (patt[pos] == '%')
			sel *= FULL_WILDCARD_SEL;
		else if (patt[pos] == '_')
			sel *= ANY_CHAR_SEL;
		else if (patt[pos] == '\\')
		{
			/* Backslash quotes the next character */
			pos++;
			if (pos >= pattlen)
				break;
			sel *= FIXED_CHAR_SEL;
		}
		else
			sel *= FIXED_CHAR_SEL;
	}
	/* Could get sel > 1 if multiple wildcards */
	if (sel > 1.0)
		sel = 1.0;
	return sel;
}