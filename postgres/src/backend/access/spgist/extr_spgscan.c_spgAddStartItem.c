#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  zeroDistances; } ;
struct TYPE_8__ {int isLeaf; int recheck; int recheckDistances; int /*<<< orphan*/ * traversalValue; scalar_t__ value; scalar_t__ level; int /*<<< orphan*/  heapPtr; } ;
typedef  TYPE_1__ SpGistSearchItem ;
typedef  TYPE_2__* SpGistScanOpaque ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPGIST_NULL_BLKNO ; 
 int /*<<< orphan*/  SPGIST_ROOT_BLKNO ; 
 int /*<<< orphan*/  spgAddSearchItemToQueue (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* spgAllocSearchItem (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spgAddStartItem(SpGistScanOpaque so, bool isnull)
{
	SpGistSearchItem *startEntry =
	spgAllocSearchItem(so, isnull, so->zeroDistances);

	ItemPointerSet(&startEntry->heapPtr,
				   isnull ? SPGIST_NULL_BLKNO : SPGIST_ROOT_BLKNO,
				   FirstOffsetNumber);
	startEntry->isLeaf = false;
	startEntry->level = 0;
	startEntry->value = (Datum) 0;
	startEntry->traversalValue = NULL;
	startEntry->recheck = false;
	startEntry->recheckDistances = false;

	spgAddSearchItemToQueue(so, startEntry);
}