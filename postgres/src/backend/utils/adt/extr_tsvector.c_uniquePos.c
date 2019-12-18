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
typedef  int /*<<< orphan*/  WordEntryPos ;

/* Variables and functions */
 int MAXENTRYPOS ; 
 int MAXNUMPOS ; 
 int WEP_GETPOS (int /*<<< orphan*/ ) ; 
 scalar_t__ WEP_GETWEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEP_SETWEIGHT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  compareWordEntryPos ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uniquePos(WordEntryPos *a, int l)
{
	WordEntryPos *ptr,
			   *res;

	if (l <= 1)
		return l;

	qsort((void *) a, l, sizeof(WordEntryPos), compareWordEntryPos);

	res = a;
	ptr = a + 1;
	while (ptr - a < l)
	{
		if (WEP_GETPOS(*ptr) != WEP_GETPOS(*res))
		{
			res++;
			*res = *ptr;
			if (res - a >= MAXNUMPOS - 1 ||
				WEP_GETPOS(*res) == MAXENTRYPOS - 1)
				break;
		}
		else if (WEP_GETWEIGHT(*ptr) > WEP_GETWEIGHT(*res))
			WEP_SETWEIGHT(*res, WEP_GETWEIGHT(*ptr));
		ptr++;
	}

	return res + 1 - a;
}