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
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {scalar_t__ off; int /*<<< orphan*/  blkno; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ GinBtreeStack ;
typedef  TYPE_2__ GinBtreeData ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 scalar_t__ GinPageRightMost (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginStepRight (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
moveRightIfItNeeded(GinBtreeData *btree, GinBtreeStack *stack, Snapshot snapshot)
{
	Page		page = BufferGetPage(stack->buffer);

	if (stack->off > PageGetMaxOffsetNumber(page))
	{
		/*
		 * We scanned the whole page, so we should take right page
		 */
		if (GinPageRightMost(page))
			return false;		/* no more pages */

		stack->buffer = ginStepRight(stack->buffer, btree->index, GIN_SHARE);
		stack->blkno = BufferGetBlockNumber(stack->buffer);
		stack->off = FirstOffsetNumber;
		PredicateLockPage(btree->index, stack->blkno, snapshot);
	}

	return true;
}