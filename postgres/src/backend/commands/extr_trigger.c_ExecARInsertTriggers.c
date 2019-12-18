#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {scalar_t__ trig_insert_after_row; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_9__ {scalar_t__ tcs_insert_new_table; } ;
typedef  TYPE_2__ TransitionCaptureState ;
struct TYPE_10__ {TYPE_1__* ri_TrigDesc; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerSaveEvent (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  TRIGGER_EVENT_INSERT ; 

void
ExecARInsertTriggers(EState *estate, ResultRelInfo *relinfo,
					 TupleTableSlot *slot, List *recheckIndexes,
					 TransitionCaptureState *transition_capture)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;

	if ((trigdesc && trigdesc->trig_insert_after_row) ||
		(transition_capture && transition_capture->tcs_insert_new_table))
		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_INSERT,
							  true, NULL, slot,
							  recheckIndexes, NULL,
							  transition_capture);
}