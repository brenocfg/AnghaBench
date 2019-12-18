#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_11__ {scalar_t__ trig_update_after_row; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_12__ {scalar_t__ tcs_update_new_table; scalar_t__ tcs_update_old_table; } ;
typedef  TYPE_2__ TransitionCaptureState ;
struct TYPE_13__ {TYPE_1__* ri_TrigDesc; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerSaveEvent (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ExecGetTriggerOldSlot (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  GetAllUpdatedColumns (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTupleForTrigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockTupleExclusive ; 
 int /*<<< orphan*/  TRIGGER_EVENT_UPDATE ; 

void
ExecARUpdateTriggers(EState *estate, ResultRelInfo *relinfo,
					 ItemPointer tupleid,
					 HeapTuple fdw_trigtuple,
					 TupleTableSlot *newslot,
					 List *recheckIndexes,
					 TransitionCaptureState *transition_capture)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;
	TupleTableSlot *oldslot = ExecGetTriggerOldSlot(estate, relinfo);

	ExecClearTuple(oldslot);

	if ((trigdesc && trigdesc->trig_update_after_row) ||
		(transition_capture &&
		 (transition_capture->tcs_update_old_table ||
		  transition_capture->tcs_update_new_table)))
	{
		/*
		 * Note: if the UPDATE is converted into a DELETE+INSERT as part of
		 * update-partition-key operation, then this function is also called
		 * separately for DELETE and INSERT to capture transition table rows.
		 * In such case, either old tuple or new tuple can be NULL.
		 */
		if (fdw_trigtuple == NULL && ItemPointerIsValid(tupleid))
			GetTupleForTrigger(estate,
							   NULL,
							   relinfo,
							   tupleid,
							   LockTupleExclusive,
							   oldslot,
							   NULL);
		else if (fdw_trigtuple != NULL)
			ExecForceStoreHeapTuple(fdw_trigtuple, oldslot, false);

		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_UPDATE,
							  true, oldslot, newslot, recheckIndexes,
							  GetAllUpdatedColumns(relinfo, estate),
							  transition_capture);
	}
}