#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* result; int /*<<< orphan*/  callback_state; scalar_t__ (* callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int tuples_removed; int num_index_tuples; } ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  TYPE_2__ GinVacuumState ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ItemPointer
ginVacuumItemPointers(GinVacuumState *gvs, ItemPointerData *items,
					  int nitem, int *nremaining)
{
	int			i,
				remaining = 0;
	ItemPointer tmpitems = NULL;

	/*
	 * Iterate over TIDs array
	 */
	for (i = 0; i < nitem; i++)
	{
		if (gvs->callback(items + i, gvs->callback_state))
		{
			gvs->result->tuples_removed += 1;
			if (!tmpitems)
			{
				/*
				 * First TID to be deleted: allocate memory to hold the
				 * remaining items.
				 */
				tmpitems = palloc(sizeof(ItemPointerData) * nitem);
				memcpy(tmpitems, items, sizeof(ItemPointerData) * i);
			}
		}
		else
		{
			gvs->result->num_index_tuples += 1;
			if (tmpitems)
				tmpitems[remaining] = items[i];
			remaining++;
		}
	}

	*nremaining = remaining;
	return tmpitems;
}