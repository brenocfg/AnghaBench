#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* WindowStatePerFunc ;
struct TYPE_9__ {int numfuncs; scalar_t__ partcontext; scalar_t__ aggcontext; int numaggs; int partition_spooled; int /*<<< orphan*/ * buffer; TYPE_2__* peragg; TYPE_3__* perfunc; } ;
typedef  TYPE_4__ WindowAggState ;
struct TYPE_8__ {TYPE_1__* winobj; } ;
struct TYPE_7__ {scalar_t__ aggcontext; } ;
struct TYPE_6__ {int /*<<< orphan*/ * localmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (scalar_t__) ; 
 int /*<<< orphan*/  tuplestore_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_partition(WindowAggState *winstate)
{
	int			i;

	for (i = 0; i < winstate->numfuncs; i++)
	{
		WindowStatePerFunc perfuncstate = &(winstate->perfunc[i]);

		/* Release any partition-local state of this window function */
		if (perfuncstate->winobj)
			perfuncstate->winobj->localmem = NULL;
	}

	/*
	 * Release all partition-local memory (in particular, any partition-local
	 * state that we might have trashed our pointers to in the above loop, and
	 * any aggregate temp data).  We don't rely on retail pfree because some
	 * aggregates might have allocated data we don't have direct pointers to.
	 */
	MemoryContextResetAndDeleteChildren(winstate->partcontext);
	MemoryContextResetAndDeleteChildren(winstate->aggcontext);
	for (i = 0; i < winstate->numaggs; i++)
	{
		if (winstate->peragg[i].aggcontext != winstate->aggcontext)
			MemoryContextResetAndDeleteChildren(winstate->peragg[i].aggcontext);
	}

	if (winstate->buffer)
		tuplestore_end(winstate->buffer);
	winstate->buffer = NULL;
	winstate->partition_spooled = false;
}