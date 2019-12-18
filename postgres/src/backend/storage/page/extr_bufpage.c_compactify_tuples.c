#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  itemIdSortData ;
typedef  TYPE_1__* itemIdSort ;
struct TYPE_8__ {int lp_off; } ;
struct TYPE_7__ {int pd_special; int pd_upper; } ;
struct TYPE_6__ {int alignedlen; int itemoff; scalar_t__ offsetindex; } ;
typedef  TYPE_2__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  int Offset ;
typedef  TYPE_3__* ItemId ;

/* Variables and functions */
 TYPE_3__* PageGetItemId (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  itemoffcompare ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  qsort (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compactify_tuples(itemIdSort itemidbase, int nitems, Page page)
{
	PageHeader	phdr = (PageHeader) page;
	Offset		upper;
	int			i;

	/* sort itemIdSortData array into decreasing itemoff order */
	qsort((char *) itemidbase, nitems, sizeof(itemIdSortData),
		  itemoffcompare);

	upper = phdr->pd_special;
	for (i = 0; i < nitems; i++)
	{
		itemIdSort	itemidptr = &itemidbase[i];
		ItemId		lp;

		lp = PageGetItemId(page, itemidptr->offsetindex + 1);
		upper -= itemidptr->alignedlen;
		memmove((char *) page + upper,
				(char *) page + itemidptr->itemoff,
				itemidptr->alignedlen);
		lp->lp_off = upper;
	}

	phdr->pd_upper = upper;
}