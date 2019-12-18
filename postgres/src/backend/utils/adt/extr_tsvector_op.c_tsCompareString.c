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
typedef  int int32 ;

/* Variables and functions */
 int /*<<< orphan*/  Min (int,int) ; 
 int memcmp (char*,char*,int /*<<< orphan*/ ) ; 

int32
tsCompareString(char *a, int lena, char *b, int lenb, bool prefix)
{
	int			cmp;

	if (lena == 0)
	{
		if (prefix)
			cmp = 0;			/* empty string is prefix of anything */
		else
			cmp = (lenb > 0) ? -1 : 0;
	}
	else if (lenb == 0)
	{
		cmp = (lena > 0) ? 1 : 0;
	}
	else
	{
		cmp = memcmp(a, b, Min(lena, lenb));

		if (prefix)
		{
			if (cmp == 0 && lena > lenb)
				cmp = 1;		/* a is longer, so not a prefix of b */
		}
		else if (cmp == 0 && lena != lenb)
		{
			cmp = (lena < lenb) ? -1 : 1;
		}
	}

	return cmp;
}