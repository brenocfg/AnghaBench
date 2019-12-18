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
typedef  int /*<<< orphan*/  TypeCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int element_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
find_next_mcelem(Datum *mcelem, int nmcelem, Datum value, int *index,
				 TypeCacheEntry *typentry)
{
	int			l = *index,
				r = nmcelem - 1,
				i,
				res;

	while (l <= r)
	{
		i = (l + r) / 2;
		res = element_compare(&mcelem[i], &value, typentry);
		if (res == 0)
		{
			*index = i;
			return true;
		}
		else if (res < 0)
			l = i + 1;
		else
			r = i - 1;
	}
	*index = l;
	return false;
}