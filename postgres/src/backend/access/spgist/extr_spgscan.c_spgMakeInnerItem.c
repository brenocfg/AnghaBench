#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ ** traversalValues; int /*<<< orphan*/ * reconstructedValues; scalar_t__* levelAdds; } ;
typedef  TYPE_3__ spgInnerConsistentOut ;
struct TYPE_19__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_14__ {int /*<<< orphan*/  attlen; int /*<<< orphan*/  attbyval; } ;
struct TYPE_15__ {TYPE_1__ attLeafType; } ;
struct TYPE_18__ {TYPE_2__ state; } ;
struct TYPE_17__ {int isLeaf; int recheck; int recheckDistances; int /*<<< orphan*/ * traversalValue; int /*<<< orphan*/  value; scalar_t__ level; int /*<<< orphan*/  heapPtr; } ;
typedef  TYPE_4__ SpGistSearchItem ;
typedef  TYPE_5__* SpGistScanOpaque ;
typedef  TYPE_6__* SpGistNodeTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* spgAllocSearchItem (TYPE_5__*,int,double*) ; 

__attribute__((used)) static SpGistSearchItem *
spgMakeInnerItem(SpGistScanOpaque so,
				 SpGistSearchItem *parentItem,
				 SpGistNodeTuple tuple,
				 spgInnerConsistentOut *out, int i, bool isnull,
				 double *distances)
{
	SpGistSearchItem *item = spgAllocSearchItem(so, isnull, distances);

	item->heapPtr = tuple->t_tid;
	item->level = out->levelAdds ? parentItem->level + out->levelAdds[i]
		: parentItem->level;

	/* Must copy value out of temp context */
	item->value = out->reconstructedValues
		? datumCopy(out->reconstructedValues[i],
					so->state.attLeafType.attbyval,
					so->state.attLeafType.attlen)
		: (Datum) 0;

	/*
	 * Elements of out.traversalValues should be allocated in
	 * in.traversalMemoryContext, which is actually a long lived context of
	 * index scan.
	 */
	item->traversalValue =
		out->traversalValues ? out->traversalValues[i] : NULL;

	item->isLeaf = false;
	item->recheck = false;
	item->recheckDistances = false;

	return item;
}