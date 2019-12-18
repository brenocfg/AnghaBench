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
typedef  size_t uint32 ;
struct TYPE_4__ {scalar_t__ nitems; size_t lastidx; size_t capacity; scalar_t__* itemsarr; scalar_t__ invalidval; } ;
typedef  TYPE_1__ ResourceArray ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 scalar_t__ RESARRAY_IS_ARRAY (TYPE_1__*) ; 

__attribute__((used)) static bool
ResourceArrayGetAny(ResourceArray *resarr, Datum *value)
{
	if (resarr->nitems == 0)
		return false;

	if (RESARRAY_IS_ARRAY(resarr))
	{
		/* Linear array: just return the first element. */
		resarr->lastidx = 0;
	}
	else
	{
		/* Hash: search forward from wherever we were last. */
		uint32		mask = resarr->capacity - 1;

		for (;;)
		{
			resarr->lastidx &= mask;
			if (resarr->itemsarr[resarr->lastidx] != resarr->invalidval)
				break;
			resarr->lastidx++;
		}
	}

	*value = resarr->itemsarr[resarr->lastidx];
	return true;
}