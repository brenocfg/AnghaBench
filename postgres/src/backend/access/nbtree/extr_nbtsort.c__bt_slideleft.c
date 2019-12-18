#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/ * ItemId ;

/* Variables and functions */
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 scalar_t__ P_FIRSTKEY ; 
 scalar_t__ P_HIKEY ; 
 int /*<<< orphan*/ * PageGetItemId (scalar_t__,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (scalar_t__) ; 
 int /*<<< orphan*/  PageIsEmpty (scalar_t__) ; 

__attribute__((used)) static void
_bt_slideleft(Page page)
{
	OffsetNumber off;
	OffsetNumber maxoff;
	ItemId		previi;
	ItemId		thisii;

	if (!PageIsEmpty(page))
	{
		maxoff = PageGetMaxOffsetNumber(page);
		previi = PageGetItemId(page, P_HIKEY);
		for (off = P_FIRSTKEY; off <= maxoff; off = OffsetNumberNext(off))
		{
			thisii = PageGetItemId(page, off);
			*previi = *thisii;
			previi = thisii;
		}
		((PageHeader) page)->pd_lower -= sizeof(ItemIdData);
	}
}