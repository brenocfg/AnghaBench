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
struct TYPE_6__ {struct TYPE_6__* aux_fmstate; } ;
struct TYPE_5__ {scalar_t__ ri_FdwState; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  TYPE_2__ PgFdwModifyState ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_foreign_modify (TYPE_2__*) ; 

__attribute__((used)) static void
postgresEndForeignInsert(EState *estate,
						 ResultRelInfo *resultRelInfo)
{
	PgFdwModifyState *fmstate = (PgFdwModifyState *) resultRelInfo->ri_FdwState;

	Assert(fmstate != NULL);

	/*
	 * If the fmstate has aux_fmstate set, get the aux_fmstate (see
	 * postgresBeginForeignInsert())
	 */
	if (fmstate->aux_fmstate)
		fmstate = fmstate->aux_fmstate;

	/* Destroy the execution state */
	finish_foreign_modify(fmstate);
}