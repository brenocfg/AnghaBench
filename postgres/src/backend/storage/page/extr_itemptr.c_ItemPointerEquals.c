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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemPointer ;

/* Variables and functions */
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 

bool
ItemPointerEquals(ItemPointer pointer1, ItemPointer pointer2)
{
	/*
	 * We really want ItemPointerData to be exactly 6 bytes.  This is rather a
	 * random place to check, but there is no better place.
	 */
	StaticAssertStmt(sizeof(ItemPointerData) == 3 * sizeof(uint16),
					 "ItemPointerData struct is improperly padded");

	if (ItemPointerGetBlockNumber(pointer1) ==
		ItemPointerGetBlockNumber(pointer2) &&
		ItemPointerGetOffsetNumber(pointer1) ==
		ItemPointerGetOffsetNumber(pointer2))
		return true;
	else
		return false;
}