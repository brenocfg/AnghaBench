#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  GinStatsData ;
typedef  TYPE_1__ GinBtreeStack ;
typedef  int /*<<< orphan*/  GinBtree ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 scalar_t__ GinPageIsIncompleteSplit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeGinBtreeStack (TYPE_1__*) ; 
 int /*<<< orphan*/  ginFinishSplit (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int ginPlaceToPage (int /*<<< orphan*/ ,TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ginInsertValue(GinBtree btree, GinBtreeStack *stack, void *insertdata,
			   GinStatsData *buildStats)
{
	bool		done;

	/* If the leaf page was incompletely split, finish the split first */
	if (GinPageIsIncompleteSplit(BufferGetPage(stack->buffer)))
		ginFinishSplit(btree, stack, false, buildStats);

	done = ginPlaceToPage(btree, stack,
						  insertdata, InvalidBlockNumber,
						  InvalidBuffer, buildStats);
	if (done)
	{
		LockBuffer(stack->buffer, GIN_UNLOCK);
		freeGinBtreeStack(stack);
	}
	else
		ginFinishSplit(btree, stack, true, buildStats);
}