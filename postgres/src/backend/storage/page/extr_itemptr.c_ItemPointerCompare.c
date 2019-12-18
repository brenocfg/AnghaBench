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
typedef  int int32 ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ ItemPointerGetBlockNumberNoCheck (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerGetOffsetNumberNoCheck (int /*<<< orphan*/ ) ; 

int32
ItemPointerCompare(ItemPointer arg1, ItemPointer arg2)
{
	/*
	 * Use ItemPointerGet{Offset,Block}NumberNoCheck to avoid asserting
	 * ip_posid != 0, which may not be true for a user-supplied TID.
	 */
	BlockNumber b1 = ItemPointerGetBlockNumberNoCheck(arg1);
	BlockNumber b2 = ItemPointerGetBlockNumberNoCheck(arg2);

	if (b1 < b2)
		return -1;
	else if (b1 > b2)
		return 1;
	else if (ItemPointerGetOffsetNumberNoCheck(arg1) <
			 ItemPointerGetOffsetNumberNoCheck(arg2))
		return -1;
	else if (ItemPointerGetOffsetNumberNoCheck(arg1) >
			 ItemPointerGetOffsetNumberNoCheck(arg2))
		return 1;
	else
		return 0;
}