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
struct TYPE_4__ {int /*<<< orphan*/  lp_flags; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  TYPE_1__* ItemId ;

/* Variables and functions */
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ ItemIdIsUsed (TYPE_1__*) ; 
 int /*<<< orphan*/  LP_UNUSED ; 
 scalar_t__ OffsetNumberNext (scalar_t__) ; 
 TYPE_1__* PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 

void
mask_lp_flags(Page page)
{
	OffsetNumber offnum,
				maxoff;

	maxoff = PageGetMaxOffsetNumber(page);
	for (offnum = FirstOffsetNumber;
		 offnum <= maxoff;
		 offnum = OffsetNumberNext(offnum))
	{
		ItemId		itemId = PageGetItemId(page, offnum);

		if (ItemIdIsUsed(itemId))
			itemId->lp_flags = LP_UNUSED;
	}
}