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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {struct TYPE_6__* aux_fmstate; } ;
struct TYPE_5__ {TYPE_2__* ri_FdwState; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  TYPE_2__ PgFdwModifyState ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_INSERT ; 
 int /*<<< orphan*/ * execute_foreign_modify (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
postgresExecForeignInsert(EState *estate,
						  ResultRelInfo *resultRelInfo,
						  TupleTableSlot *slot,
						  TupleTableSlot *planSlot)
{
	PgFdwModifyState *fmstate = (PgFdwModifyState *) resultRelInfo->ri_FdwState;
	TupleTableSlot *rslot;

	/*
	 * If the fmstate has aux_fmstate set, use the aux_fmstate (see
	 * postgresBeginForeignInsert())
	 */
	if (fmstate->aux_fmstate)
		resultRelInfo->ri_FdwState = fmstate->aux_fmstate;
	rslot = execute_foreign_modify(estate, resultRelInfo, CMD_INSERT,
								   slot, planSlot);
	/* Revert that change */
	if (fmstate->aux_fmstate)
		resultRelInfo->ri_FdwState = fmstate;

	return rslot;
}