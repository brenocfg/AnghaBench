#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  allocatedMemory; } ;
struct TYPE_3__ {int count; int maxcount; int shouldSort; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  RBTNode ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_1__ GinEntryAccumulator ;
typedef  TYPE_2__ BuildAccumulator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetMemoryChunkSpace (int /*<<< orphan*/ *) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ repalloc_huge (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ginCombineData(RBTNode *existing, const RBTNode *newdata, void *arg)
{
	GinEntryAccumulator *eo = (GinEntryAccumulator *) existing;
	const GinEntryAccumulator *en = (const GinEntryAccumulator *) newdata;
	BuildAccumulator *accum = (BuildAccumulator *) arg;

	/*
	 * Note this code assumes that newdata contains only one itempointer.
	 */
	if (eo->count >= eo->maxcount)
	{
		if (eo->maxcount > INT_MAX)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("posting list is too long"),
					 errhint("Reduce maintenance_work_mem.")));

		accum->allocatedMemory -= GetMemoryChunkSpace(eo->list);
		eo->maxcount *= 2;
		eo->list = (ItemPointerData *)
			repalloc_huge(eo->list, sizeof(ItemPointerData) * eo->maxcount);
		accum->allocatedMemory += GetMemoryChunkSpace(eo->list);
	}

	/* If item pointers are not ordered, they will need to be sorted later */
	if (eo->shouldSort == false)
	{
		int			res;

		res = ginCompareItemPointers(eo->list + eo->count - 1, en->list);
		Assert(res != 0);

		if (res > 0)
			eo->shouldSort = true;
	}

	eo->list[eo->count] = en->list[0];
	eo->count++;
}