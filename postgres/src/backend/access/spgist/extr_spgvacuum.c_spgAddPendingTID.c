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
struct TYPE_4__ {int done; struct TYPE_4__* next; int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__ spgVacPendingItem ;
struct TYPE_5__ {TYPE_1__* pendingList; } ;
typedef  TYPE_2__ spgBulkDeleteState ;
typedef  int /*<<< orphan*/ * ItemPointer ;

/* Variables and functions */
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
spgAddPendingTID(spgBulkDeleteState *bds, ItemPointer tid)
{
	spgVacPendingItem *pitem;
	spgVacPendingItem **listLink;

	/* search the list for pre-existing entry */
	listLink = &bds->pendingList;
	while (*listLink != NULL)
	{
		pitem = *listLink;
		if (ItemPointerEquals(tid, &pitem->tid))
			return;				/* already in list, do nothing */
		listLink = &pitem->next;
	}
	/* not there, so append new entry */
	pitem = (spgVacPendingItem *) palloc(sizeof(spgVacPendingItem));
	pitem->tid = *tid;
	pitem->done = false;
	pitem->next = NULL;
	*listLink = pitem;
}