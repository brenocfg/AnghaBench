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
typedef  int uint32 ;
struct TYPE_4__ {scalar_t__* itemsarr; int capacity; scalar_t__ invalidval; scalar_t__ maxitems; scalar_t__ nitems; } ;
typedef  TYPE_1__ ResourceArray ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int RESARRAY_INIT_SIZE ; 
 scalar_t__ RESARRAY_MAX_ITEMS (int) ; 
 int /*<<< orphan*/  ResourceArrayAdd (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  pfree (scalar_t__*) ; 

__attribute__((used)) static void
ResourceArrayEnlarge(ResourceArray *resarr)
{
	uint32		i,
				oldcap,
				newcap;
	Datum	   *olditemsarr;
	Datum	   *newitemsarr;

	if (resarr->nitems < resarr->maxitems)
		return;					/* no work needed */

	olditemsarr = resarr->itemsarr;
	oldcap = resarr->capacity;

	/* Double the capacity of the array (capacity must stay a power of 2!) */
	newcap = (oldcap > 0) ? oldcap * 2 : RESARRAY_INIT_SIZE;
	newitemsarr = (Datum *) MemoryContextAlloc(TopMemoryContext,
											   newcap * sizeof(Datum));
	for (i = 0; i < newcap; i++)
		newitemsarr[i] = resarr->invalidval;

	/* We assume we can't fail below this point, so OK to scribble on resarr */
	resarr->itemsarr = newitemsarr;
	resarr->capacity = newcap;
	resarr->maxitems = RESARRAY_MAX_ITEMS(newcap);
	resarr->nitems = 0;

	if (olditemsarr != NULL)
	{
		/*
		 * Transfer any pre-existing entries into the new array; they don't
		 * necessarily go where they were before, so this simple logic is the
		 * best way.  Note that if we were managing the set as a simple array,
		 * the entries after nitems are garbage, but that shouldn't matter
		 * because we won't get here unless nitems was equal to oldcap.
		 */
		for (i = 0; i < oldcap; i++)
		{
			if (olditemsarr[i] != resarr->invalidval)
				ResourceArrayAdd(resarr, olditemsarr[i]);
		}

		/* And release old array. */
		pfree(olditemsarr);
	}

	Assert(resarr->nitems < resarr->maxitems);
}