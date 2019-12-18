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
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  scalar_t__ ItemPointer ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  int /*<<< orphan*/  GinState ;
typedef  int /*<<< orphan*/  GinPostingList ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int GinGetNPosting (int /*<<< orphan*/ ) ; 
 scalar_t__ GinGetPosting (int /*<<< orphan*/ ) ; 
 scalar_t__ GinItupIsCompressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ ginPostingListDecode (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ palloc (int) ; 

ItemPointer
ginReadTuple(GinState *ginstate, OffsetNumber attnum, IndexTuple itup,
			 int *nitems)
{
	Pointer		ptr = GinGetPosting(itup);
	int			nipd = GinGetNPosting(itup);
	ItemPointer ipd;
	int			ndecoded;

	if (GinItupIsCompressed(itup))
	{
		if (nipd > 0)
		{
			ipd = ginPostingListDecode((GinPostingList *) ptr, &ndecoded);
			if (nipd != ndecoded)
				elog(ERROR, "number of items mismatch in GIN entry tuple, %d in tuple header, %d decoded",
					 nipd, ndecoded);
		}
		else
		{
			ipd = palloc(0);
		}
	}
	else
	{
		ipd = (ItemPointer) palloc(sizeof(ItemPointerData) * nipd);
		memcpy(ipd, ptr, sizeof(ItemPointerData) * nipd);
	}
	*nitems = nipd;
	return ipd;
}