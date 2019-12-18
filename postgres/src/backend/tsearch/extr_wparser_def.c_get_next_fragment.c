#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* words; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  repeated; scalar_t__ item; } ;
typedef  TYPE_2__ HeadlineParsedText ;

/* Variables and functions */
 int /*<<< orphan*/  NONWORDTOKEN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_next_fragment(HeadlineParsedText *prs, int *startpos, int *endpos,
				  int *curlen, int *poslen, int max_words)
{
	int			i;

	/*
	 * Objective: Generate a fragment of words between startpos and endpos
	 * such that it has at most max_words and both ends has query words. If
	 * the startpos and endpos are the endpoints of the cover and the cover
	 * has fewer words than max_words, then this function should just return
	 * the cover
	 */
	/* first move startpos to an item */
	for (i = *startpos; i <= *endpos; i++)
	{
		*startpos = i;
		if (prs->words[i].item && !prs->words[i].repeated)
			break;
	}
	/* cut endpos to have only max_words */
	*curlen = 0;
	*poslen = 0;
	for (i = *startpos; i <= *endpos && *curlen < max_words; i++)
	{
		if (!NONWORDTOKEN(prs->words[i].type))
			*curlen += 1;
		if (prs->words[i].item && !prs->words[i].repeated)
			*poslen += 1;
	}
	/* if the cover was cut then move back endpos to a query item */
	if (*endpos > i)
	{
		*endpos = i;
		for (i = *endpos; i >= *startpos; i--)
		{
			*endpos = i;
			if (prs->words[i].item && !prs->words[i].repeated)
				break;
			if (!NONWORDTOKEN(prs->words[i].type))
				*curlen -= 1;
		}
	}
}