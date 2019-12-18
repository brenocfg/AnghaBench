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
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
_bt_adjacenthtid(ItemPointer lowhtid, ItemPointer highhtid)
{
	BlockNumber lowblk,
				highblk;

	lowblk = ItemPointerGetBlockNumber(lowhtid);
	highblk = ItemPointerGetBlockNumber(highhtid);

	/* Make optimistic assumption of adjacency when heap blocks match */
	if (lowblk == highblk)
		return true;

	/* When heap block one up, second offset should be FirstOffsetNumber */
	if (lowblk + 1 == highblk &&
		ItemPointerGetOffsetNumber(highhtid) == FirstOffsetNumber)
		return true;

	return false;
}