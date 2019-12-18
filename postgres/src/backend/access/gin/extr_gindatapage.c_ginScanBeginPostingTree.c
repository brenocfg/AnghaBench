#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fullScan; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  GinBtreeStack ;
typedef  TYPE_1__* GinBtree ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/ * ginFindLeafPage (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginPrepareDataScan (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GinBtreeStack *
ginScanBeginPostingTree(GinBtree btree, Relation index, BlockNumber rootBlkno,
						Snapshot snapshot)
{
	GinBtreeStack *stack;

	ginPrepareDataScan(btree, index, rootBlkno);

	btree->fullScan = true;

	stack = ginFindLeafPage(btree, true, false, snapshot);

	return stack;
}