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
struct TYPE_4__ {scalar_t__ invalidval; scalar_t__ nitems; scalar_t__ maxitems; size_t capacity; scalar_t__* itemsarr; size_t lastidx; } ;
typedef  TYPE_1__ ResourceArray ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ RESARRAY_IS_ARRAY (TYPE_1__*) ; 
 int /*<<< orphan*/  hash_any (void*,int) ; 

__attribute__((used)) static void
ResourceArrayAdd(ResourceArray *resarr, Datum value)
{
	uint32		idx;

	Assert(value != resarr->invalidval);
	Assert(resarr->nitems < resarr->maxitems);

	if (RESARRAY_IS_ARRAY(resarr))
	{
		/* Append to linear array. */
		idx = resarr->nitems;
	}
	else
	{
		/* Insert into first free slot at or after hash location. */
		uint32		mask = resarr->capacity - 1;

		idx = DatumGetUInt32(hash_any((void *) &value, sizeof(value))) & mask;
		for (;;)
		{
			if (resarr->itemsarr[idx] == resarr->invalidval)
				break;
			idx = (idx + 1) & mask;
		}
	}
	resarr->lastidx = idx;
	resarr->itemsarr[idx] = value;
	resarr->nitems++;
}