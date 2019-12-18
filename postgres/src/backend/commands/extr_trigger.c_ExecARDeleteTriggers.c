#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_10__ {scalar_t__ trig_delete_after_row; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_11__ {scalar_t__ tcs_delete_old_table; } ;
typedef  TYPE_2__ TransitionCaptureState ;
struct TYPE_12__ {TYPE_1__* ri_TrigDesc; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerSaveEvent (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ExecGetTriggerOldSlot (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  GetTupleForTrigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockTupleExclusive ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  TRIGGER_EVENT_DELETE ; 

void
ExecARDeleteTriggers(EState *estate, ResultRelInfo *relinfo,
					 ItemPointer tupleid,
					 HeapTuple fdw_trigtuple,
					 TransitionCaptureState *transition_capture)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;
	TupleTableSlot *slot = ExecGetTriggerOldSlot(estate, relinfo);

	if ((trigdesc && trigdesc->trig_delete_after_row) ||
		(transition_capture && transition_capture->tcs_delete_old_table))
	{
		Assert(HeapTupleIsValid(fdw_trigtuple) ^ ItemPointerIsValid(tupleid));
		if (fdw_trigtuple == NULL)
			GetTupleForTrigger(estate,
							   NULL,
							   relinfo,
							   tupleid,
							   LockTupleExclusive,
							   slot,
							   NULL);
		else
			ExecForceStoreHeapTuple(fdw_trigtuple, slot, false);

		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_DELETE,
							  true, slot, NULL, NIL, NULL,
							  transition_capture);
	}
}