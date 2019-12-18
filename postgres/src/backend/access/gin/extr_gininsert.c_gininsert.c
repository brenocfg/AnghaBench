#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* origTupdesc; } ;
struct TYPE_10__ {void* ii_AmCache; int /*<<< orphan*/  ii_Context; } ;
struct TYPE_9__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  IndexUniqueCheck ;
typedef  TYPE_2__ IndexInfo ;
typedef  int /*<<< orphan*/  GinTupleCollector ;
typedef  TYPE_3__ GinState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ GinGetUseFastUpdate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginHeapTupleFastCollect (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginHeapTupleFastInsert (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginHeapTupleInsert (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initGinState (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 

bool
gininsert(Relation index, Datum *values, bool *isnull,
		  ItemPointer ht_ctid, Relation heapRel,
		  IndexUniqueCheck checkUnique,
		  IndexInfo *indexInfo)
{
	GinState   *ginstate = (GinState *) indexInfo->ii_AmCache;
	MemoryContext oldCtx;
	MemoryContext insertCtx;
	int			i;

	/* Initialize GinState cache if first call in this statement */
	if (ginstate == NULL)
	{
		oldCtx = MemoryContextSwitchTo(indexInfo->ii_Context);
		ginstate = (GinState *) palloc(sizeof(GinState));
		initGinState(ginstate, index);
		indexInfo->ii_AmCache = (void *) ginstate;
		MemoryContextSwitchTo(oldCtx);
	}

	insertCtx = AllocSetContextCreate(CurrentMemoryContext,
									  "Gin insert temporary context",
									  ALLOCSET_DEFAULT_SIZES);

	oldCtx = MemoryContextSwitchTo(insertCtx);

	if (GinGetUseFastUpdate(index))
	{
		GinTupleCollector collector;

		memset(&collector, 0, sizeof(GinTupleCollector));

		for (i = 0; i < ginstate->origTupdesc->natts; i++)
			ginHeapTupleFastCollect(ginstate, &collector,
									(OffsetNumber) (i + 1),
									values[i], isnull[i],
									ht_ctid);

		ginHeapTupleFastInsert(ginstate, &collector);
	}
	else
	{
		for (i = 0; i < ginstate->origTupdesc->natts; i++)
			ginHeapTupleInsert(ginstate, (OffsetNumber) (i + 1),
							   values[i], isnull[i],
							   ht_ctid);
	}

	MemoryContextSwitchTo(oldCtx);
	MemoryContextDelete(insertCtx);

	return false;
}