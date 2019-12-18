#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int isData; int fullScan; int isBuild; int /*<<< orphan*/  entryCategory; int /*<<< orphan*/  entryKey; int /*<<< orphan*/  entryAttnum; int /*<<< orphan*/  prepareDownlink; int /*<<< orphan*/  fillRoot; int /*<<< orphan*/  execPlaceToPage; int /*<<< orphan*/  beginPlaceToPage; int /*<<< orphan*/  findChildPtr; int /*<<< orphan*/  findItem; int /*<<< orphan*/  isMoveRight; int /*<<< orphan*/  getLeftMostChild; int /*<<< orphan*/  findChildPage; TYPE_1__* ginstate; int /*<<< orphan*/  rootBlkno; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  TYPE_1__ GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  GinBtreeData ;
typedef  TYPE_2__* GinBtree ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  GIN_ROOT_BLKNO ; 
 int /*<<< orphan*/  entryBeginPlaceToPage ; 
 int /*<<< orphan*/  entryExecPlaceToPage ; 
 int /*<<< orphan*/  entryFindChildPtr ; 
 int /*<<< orphan*/  entryGetLeftMostPage ; 
 int /*<<< orphan*/  entryIsMoveRight ; 
 int /*<<< orphan*/  entryLocateEntry ; 
 int /*<<< orphan*/  entryLocateLeafEntry ; 
 int /*<<< orphan*/  entryPrepareDownlink ; 
 int /*<<< orphan*/  ginEntryFillRoot ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
ginPrepareEntryScan(GinBtree btree, OffsetNumber attnum,
					Datum key, GinNullCategory category,
					GinState *ginstate)
{
	memset(btree, 0, sizeof(GinBtreeData));

	btree->index = ginstate->index;
	btree->rootBlkno = GIN_ROOT_BLKNO;
	btree->ginstate = ginstate;

	btree->findChildPage = entryLocateEntry;
	btree->getLeftMostChild = entryGetLeftMostPage;
	btree->isMoveRight = entryIsMoveRight;
	btree->findItem = entryLocateLeafEntry;
	btree->findChildPtr = entryFindChildPtr;
	btree->beginPlaceToPage = entryBeginPlaceToPage;
	btree->execPlaceToPage = entryExecPlaceToPage;
	btree->fillRoot = ginEntryFillRoot;
	btree->prepareDownlink = entryPrepareDownlink;

	btree->isData = false;
	btree->fullScan = false;
	btree->isBuild = false;

	btree->entryAttnum = attnum;
	btree->entryKey = key;
	btree->entryCategory = category;
}