#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  size_t uint32 ;
struct TYPE_4__ {size_t lastidx; scalar_t__ invalidval; size_t nitems; scalar_t__* itemsarr; int capacity; } ;
typedef  TYPE_1__ ResourceArray ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ RESARRAY_IS_ARRAY (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_any (void*,int) ; 

__attribute__((used)) static bool
ResourceArrayRemove(ResourceArray *resarr, Datum value)
{
	uint32		i,
				idx,
				lastidx = resarr->lastidx;

	Assert(value != resarr->invalidval);

	/* Search through all items, but try lastidx first. */
	if (RESARRAY_IS_ARRAY(resarr))
	{
		if (lastidx < resarr->nitems &&
			resarr->itemsarr[lastidx] == value)
		{
			resarr->itemsarr[lastidx] = resarr->itemsarr[resarr->nitems - 1];
			resarr->nitems--;
			/* Update lastidx to make reverse-order removals fast. */
			resarr->lastidx = resarr->nitems - 1;
			return true;
		}
		for (i = 0; i < resarr->nitems; i++)
		{
			if (resarr->itemsarr[i] == value)
			{
				resarr->itemsarr[i] = resarr->itemsarr[resarr->nitems - 1];
				resarr->nitems--;
				/* Update lastidx to make reverse-order removals fast. */
				resarr->lastidx = resarr->nitems - 1;
				return true;
			}
		}
	}
	else
	{
		uint32		mask = resarr->capacity - 1;

		if (lastidx < resarr->capacity &&
			resarr->itemsarr[lastidx] == value)
		{
			resarr->itemsarr[lastidx] = resarr->invalidval;
			resarr->nitems--;
			return true;
		}
		idx = DatumGetUInt32(hash_any((void *) &value, sizeof(value))) & mask;
		for (i = 0; i < resarr->capacity; i++)
		{
			if (resarr->itemsarr[idx] == value)
			{
				resarr->itemsarr[idx] = resarr->invalidval;
				resarr->nitems--;
				return true;
			}
			idx = (idx + 1) & mask;
		}
	}

	return false;
}