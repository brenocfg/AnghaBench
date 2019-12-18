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
typedef  size_t OffsetNumber ;

/* Variables and functions */

__attribute__((used)) static void
removeDontCares(OffsetNumber *a, int *len, const bool *dontcare)
{
	int			origlen,
				newlen,
				i;
	OffsetNumber *curwpos;

	origlen = newlen = *len;
	curwpos = a;
	for (i = 0; i < origlen; i++)
	{
		OffsetNumber ai = a[i];

		if (dontcare[ai] == false)
		{
			/* re-emit item into a[] */
			*curwpos = ai;
			curwpos++;
		}
		else
			newlen--;
	}

	*len = newlen;
}