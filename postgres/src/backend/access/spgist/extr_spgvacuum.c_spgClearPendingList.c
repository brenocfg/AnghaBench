#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  done; struct TYPE_5__* next; } ;
typedef  TYPE_1__ spgVacPendingItem ;
struct TYPE_6__ {TYPE_1__* pendingList; } ;
typedef  TYPE_2__ spgBulkDeleteState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
spgClearPendingList(spgBulkDeleteState *bds)
{
	spgVacPendingItem *pitem;
	spgVacPendingItem *nitem;

	for (pitem = bds->pendingList; pitem != NULL; pitem = nitem)
	{
		nitem = pitem->next;
		/* All items in list should have been dealt with */
		Assert(pitem->done);
		pfree(pitem);
	}
	bds->pendingList = NULL;
}