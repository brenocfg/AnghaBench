#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ procs; scalar_t__ nProcs; TYPE_2__* lock; } ;
struct TYPE_10__ {TYPE_2__* lock; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_9__ {TYPE_1__ waitProcs; } ;
typedef  TYPE_2__ LOCK ;
typedef  TYPE_3__ EDGE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int MaxBackends ; 
 int /*<<< orphan*/  TopoSort (TYPE_2__*,TYPE_3__*,int,scalar_t__) ; 
 size_t nWaitOrders ; 
 scalar_t__ waitOrderProcs ; 
 TYPE_4__* waitOrders ; 

__attribute__((used)) static bool
ExpandConstraints(EDGE *constraints,
				  int nConstraints)
{
	int			nWaitOrderProcs = 0;
	int			i,
				j;

	nWaitOrders = 0;

	/*
	 * Scan constraint list backwards.  This is because the last-added
	 * constraint is the only one that could fail, and so we want to test it
	 * for inconsistency first.
	 */
	for (i = nConstraints; --i >= 0;)
	{
		LOCK	   *lock = constraints[i].lock;

		/* Did we already make a list for this lock? */
		for (j = nWaitOrders; --j >= 0;)
		{
			if (waitOrders[j].lock == lock)
				break;
		}
		if (j >= 0)
			continue;
		/* No, so allocate a new list */
		waitOrders[nWaitOrders].lock = lock;
		waitOrders[nWaitOrders].procs = waitOrderProcs + nWaitOrderProcs;
		waitOrders[nWaitOrders].nProcs = lock->waitProcs.size;
		nWaitOrderProcs += lock->waitProcs.size;
		Assert(nWaitOrderProcs <= MaxBackends);

		/*
		 * Do the topo sort.  TopoSort need not examine constraints after this
		 * one, since they must be for different locks.
		 */
		if (!TopoSort(lock, constraints, i + 1,
					  waitOrders[nWaitOrders].procs))
			return false;
		nWaitOrders++;
	}
	return true;
}