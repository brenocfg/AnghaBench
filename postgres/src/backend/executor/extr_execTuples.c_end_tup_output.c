#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  slot; TYPE_2__* dest; } ;
typedef  TYPE_1__ TupOutputState ;
struct TYPE_6__ {int /*<<< orphan*/  (* rShutdown ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
end_tup_output(TupOutputState *tstate)
{
	tstate->dest->rShutdown(tstate->dest);
	/* note that destroying the dest is not ours to do */
	ExecDropSingleTupleTableSlot(tstate->slot);
	pfree(tstate);
}