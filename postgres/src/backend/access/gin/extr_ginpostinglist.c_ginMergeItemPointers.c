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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;

/* Variables and functions */
 scalar_t__ ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 

ItemPointer
ginMergeItemPointers(ItemPointerData *a, uint32 na,
					 ItemPointerData *b, uint32 nb,
					 int *nmerged)
{
	ItemPointerData *dst;

	dst = (ItemPointer) palloc((na + nb) * sizeof(ItemPointerData));

	/*
	 * If the argument arrays don't overlap, we can just append them to each
	 * other.
	 */
	if (na == 0 || nb == 0 || ginCompareItemPointers(&a[na - 1], &b[0]) < 0)
	{
		memcpy(dst, a, na * sizeof(ItemPointerData));
		memcpy(&dst[na], b, nb * sizeof(ItemPointerData));
		*nmerged = na + nb;
	}
	else if (ginCompareItemPointers(&b[nb - 1], &a[0]) < 0)
	{
		memcpy(dst, b, nb * sizeof(ItemPointerData));
		memcpy(&dst[nb], a, na * sizeof(ItemPointerData));
		*nmerged = na + nb;
	}
	else
	{
		ItemPointerData *dptr = dst;
		ItemPointerData *aptr = a;
		ItemPointerData *bptr = b;

		while (aptr - a < na && bptr - b < nb)
		{
			int			cmp = ginCompareItemPointers(aptr, bptr);

			if (cmp > 0)
				*dptr++ = *bptr++;
			else if (cmp == 0)
			{
				/* only keep one copy of the identical items */
				*dptr++ = *bptr++;
				aptr++;
			}
			else
				*dptr++ = *aptr++;
		}

		while (aptr - a < na)
			*dptr++ = *aptr++;

		while (bptr - b < nb)
			*dptr++ = *bptr++;

		*nmerged = dptr - dst;
	}

	return dst;
}