#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  itemptr; int /*<<< orphan*/  isBuild; } ;
struct TYPE_7__ {size_t nitem; size_t curitem; int /*<<< orphan*/ * items; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  GinStatsData ;
typedef  int /*<<< orphan*/  GinBtreeStack ;
typedef  TYPE_1__ GinBtreeDataLeafInsertData ;
typedef  TYPE_2__ GinBtreeData ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * ginFindLeafPage (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginInsertValue (TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginPrepareDataScan (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ginInsertItemPointers(Relation index, BlockNumber rootBlkno,
					  ItemPointerData *items, uint32 nitem,
					  GinStatsData *buildStats)
{
	GinBtreeData btree;
	GinBtreeDataLeafInsertData insertdata;
	GinBtreeStack *stack;

	ginPrepareDataScan(&btree, index, rootBlkno);
	btree.isBuild = (buildStats != NULL);
	insertdata.items = items;
	insertdata.nitem = nitem;
	insertdata.curitem = 0;

	while (insertdata.curitem < insertdata.nitem)
	{
		/* search for the leaf page where the first item should go to */
		btree.itemptr = insertdata.items[insertdata.curitem];
		stack = ginFindLeafPage(&btree, false, true, NULL);

		ginInsertValue(&btree, stack, &insertdata, buildStats);
	}
}