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
typedef  int /*<<< orphan*/  Selectivity ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP_PROBABILITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXED_CHAR_SEL ; 
 int /*<<< orphan*/  FULL_WILDCARD_SEL ; 
 int /*<<< orphan*/  pow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regex_selectivity_sub (char const*,int,int) ; 

__attribute__((used)) static Selectivity
regex_selectivity(const char *patt, int pattlen, bool case_insensitive,
				  int fixed_prefix_len)
{
	Selectivity sel;

	/* If patt doesn't end with $, consider it to have a trailing wildcard */
	if (pattlen > 0 && patt[pattlen - 1] == '$' &&
		(pattlen == 1 || patt[pattlen - 2] != '\\'))
	{
		/* has trailing $ */
		sel = regex_selectivity_sub(patt, pattlen - 1, case_insensitive);
	}
	else
	{
		/* no trailing $ */
		sel = regex_selectivity_sub(patt, pattlen, case_insensitive);
		sel *= FULL_WILDCARD_SEL;
	}

	/* If there's a fixed prefix, discount its selectivity */
	if (fixed_prefix_len > 0)
		sel /= pow(FIXED_CHAR_SEL, fixed_prefix_len);

	/* Make sure result stays in range */
	CLAMP_PROBABILITY(sel);
	return sel;
}