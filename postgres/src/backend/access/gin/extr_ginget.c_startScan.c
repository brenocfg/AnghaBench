#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_8__ {int predictNumberResult; int reduceResult; } ;
struct TYPE_7__ {size_t totalentries; size_t nkeys; scalar_t__ keys; TYPE_4__** entries; int /*<<< orphan*/  ginstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  xs_snapshot; int /*<<< orphan*/  opaque; } ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  GinState ;
typedef  TYPE_2__* GinScanOpaque ;

/* Variables and functions */
 int GinFuzzySearchLimit ; 
 int /*<<< orphan*/  startScanEntry (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startScanKey (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
startScan(IndexScanDesc scan)
{
	GinScanOpaque so = (GinScanOpaque) scan->opaque;
	GinState   *ginstate = &so->ginstate;
	uint32		i;

	for (i = 0; i < so->totalentries; i++)
		startScanEntry(ginstate, so->entries[i], scan->xs_snapshot);

	if (GinFuzzySearchLimit > 0)
	{
		/*
		 * If all of keys more than threshold we will try to reduce result, we
		 * hope (and only hope, for intersection operation of array our
		 * supposition isn't true), that total result will not more than
		 * minimal predictNumberResult.
		 */
		bool		reduce = true;

		for (i = 0; i < so->totalentries; i++)
		{
			if (so->entries[i]->predictNumberResult <= so->totalentries * GinFuzzySearchLimit)
			{
				reduce = false;
				break;
			}
		}
		if (reduce)
		{
			for (i = 0; i < so->totalentries; i++)
			{
				so->entries[i]->predictNumberResult /= so->totalentries;
				so->entries[i]->reduceResult = true;
			}
		}
	}

	/*
	 * Now that we have the estimates for the entry frequencies, finish
	 * initializing the scan keys.
	 */
	for (i = 0; i < so->nkeys; i++)
		startScanKey(ginstate, so, so->keys + i);
}