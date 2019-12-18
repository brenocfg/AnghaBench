#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int isData; int fullScan; int isBuild; int /*<<< orphan*/  prepareDownlink; int /*<<< orphan*/  fillRoot; int /*<<< orphan*/  execPlaceToPage; int /*<<< orphan*/  beginPlaceToPage; int /*<<< orphan*/  findChildPtr; int /*<<< orphan*/ * findItem; int /*<<< orphan*/  isMoveRight; int /*<<< orphan*/  getLeftMostChild; int /*<<< orphan*/  findChildPage; int /*<<< orphan*/  rootBlkno; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  GinBtreeData ;
typedef  TYPE_1__* GinBtree ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  dataBeginPlaceToPage ; 
 int /*<<< orphan*/  dataExecPlaceToPage ; 
 int /*<<< orphan*/  dataFindChildPtr ; 
 int /*<<< orphan*/  dataGetLeftMostPage ; 
 int /*<<< orphan*/  dataIsMoveRight ; 
 int /*<<< orphan*/  dataLocateItem ; 
 int /*<<< orphan*/  dataPrepareDownlink ; 
 int /*<<< orphan*/  ginDataFillRoot ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ginPrepareDataScan(GinBtree btree, Relation index, BlockNumber rootBlkno)
{
	memset(btree, 0, sizeof(GinBtreeData));

	btree->index = index;
	btree->rootBlkno = rootBlkno;

	btree->findChildPage = dataLocateItem;
	btree->getLeftMostChild = dataGetLeftMostPage;
	btree->isMoveRight = dataIsMoveRight;
	btree->findItem = NULL;
	btree->findChildPtr = dataFindChildPtr;
	btree->beginPlaceToPage = dataBeginPlaceToPage;
	btree->execPlaceToPage = dataExecPlaceToPage;
	btree->fillRoot = ginDataFillRoot;
	btree->prepareDownlink = dataPrepareDownlink;

	btree->isData = true;
	btree->fullScan = false;
	btree->isBuild = false;
}