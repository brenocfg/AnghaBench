#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  attlen; int /*<<< orphan*/  attbyval; } ;
struct TYPE_10__ {TYPE_1__ attLeafType; } ;
struct TYPE_12__ {TYPE_2__ state; } ;
struct TYPE_11__ {int level; int isLeaf; int recheck; int recheckDistances; int /*<<< orphan*/ * traversalValue; int /*<<< orphan*/  value; int /*<<< orphan*/  heapPtr; } ;
typedef  TYPE_3__ SpGistSearchItem ;
typedef  TYPE_4__* SpGistScanOpaque ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* spgAllocSearchItem (TYPE_4__*,int,double*) ; 

__attribute__((used)) static SpGistSearchItem *
spgNewHeapItem(SpGistScanOpaque so, int level, ItemPointer heapPtr,
			   Datum leafValue, bool recheck, bool recheckDistances,
			   bool isnull, double *distances)
{
	SpGistSearchItem *item = spgAllocSearchItem(so, isnull, distances);

	item->level = level;
	item->heapPtr = *heapPtr;
	/* copy value to queue cxt out of tmp cxt */
	item->value = isnull ? (Datum) 0 :
		datumCopy(leafValue, so->state.attLeafType.attbyval,
				  so->state.attLeafType.attlen);
	item->traversalValue = NULL;
	item->isLeaf = true;
	item->recheck = recheck;
	item->recheckDistances = recheckDistances;

	return item;
}