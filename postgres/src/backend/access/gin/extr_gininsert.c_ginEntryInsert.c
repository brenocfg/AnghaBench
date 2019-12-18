#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_28__ {scalar_t__ (* findItem ) (TYPE_5__*,TYPE_3__*) ;int /*<<< orphan*/  isBuild; } ;
struct TYPE_27__ {int isDelete; scalar_t__ entry; } ;
struct TYPE_26__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  off; } ;
struct TYPE_25__ {int /*<<< orphan*/  index; } ;
struct TYPE_24__ {int /*<<< orphan*/  nEntries; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_1__ GinStatsData ;
typedef  TYPE_2__ GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  TYPE_3__ GinBtreeStack ;
typedef  TYPE_4__ GinBtreeEntryInsertData ;
typedef  TYPE_5__ GinBtreeData ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckForSerializableConflictIn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 int /*<<< orphan*/  GinGetPostingTree (scalar_t__) ; 
 scalar_t__ GinIsPostingTree (scalar_t__) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ addItemPointersToLeafTuple (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ buildFreshLeafTuple (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeGinBtreeStack (TYPE_3__*) ; 
 TYPE_3__* ginFindLeafPage (TYPE_5__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginInsertItemPointers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ginInsertValue (TYPE_5__*,TYPE_3__*,TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ginPrepareEntryScan (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_3__*) ; 

void
ginEntryInsert(GinState *ginstate,
			   OffsetNumber attnum, Datum key, GinNullCategory category,
			   ItemPointerData *items, uint32 nitem,
			   GinStatsData *buildStats)
{
	GinBtreeData btree;
	GinBtreeEntryInsertData insertdata;
	GinBtreeStack *stack;
	IndexTuple	itup;
	Page		page;

	insertdata.isDelete = false;

	ginPrepareEntryScan(&btree, attnum, key, category, ginstate);
	btree.isBuild = (buildStats != NULL);

	stack = ginFindLeafPage(&btree, false, false, NULL);
	page = BufferGetPage(stack->buffer);

	if (btree.findItem(&btree, stack))
	{
		/* found pre-existing entry */
		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stack->off));

		if (GinIsPostingTree(itup))
		{
			/* add entries to existing posting tree */
			BlockNumber rootPostingTree = GinGetPostingTree(itup);

			/* release all stack */
			LockBuffer(stack->buffer, GIN_UNLOCK);
			freeGinBtreeStack(stack);

			/* insert into posting tree */
			ginInsertItemPointers(ginstate->index, rootPostingTree,
								  items, nitem,
								  buildStats);
			return;
		}

		CheckForSerializableConflictIn(ginstate->index, NULL, stack->buffer);
		/* modify an existing leaf entry */
		itup = addItemPointersToLeafTuple(ginstate, itup,
										  items, nitem, buildStats, stack->buffer);

		insertdata.isDelete = true;
	}
	else
	{
		CheckForSerializableConflictIn(ginstate->index, NULL, stack->buffer);
		/* no match, so construct a new leaf entry */
		itup = buildFreshLeafTuple(ginstate, attnum, key, category,
								   items, nitem, buildStats, stack->buffer);

		/*
		 * nEntries counts leaf tuples, so increment it only when we make a
		 * new one.
		 */
		if (buildStats)
			buildStats->nEntries++;
	}

	/* Insert the new or modified leaf tuple */
	insertdata.entry = itup;
	ginInsertValue(&btree, stack, &insertdata, buildStats);
	pfree(itup);
}