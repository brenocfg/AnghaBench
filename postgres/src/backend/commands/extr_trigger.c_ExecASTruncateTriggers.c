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
struct TYPE_5__ {scalar_t__ trig_truncate_after_statement; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_6__ {TYPE_1__* ri_TrigDesc; } ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerSaveEvent (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  TRIGGER_EVENT_TRUNCATE ; 

void
ExecASTruncateTriggers(EState *estate, ResultRelInfo *relinfo)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;

	if (trigdesc && trigdesc->trig_truncate_after_statement)
		AfterTriggerSaveEvent(estate, relinfo, TRIGGER_EVENT_TRUNCATE,
							  false, NULL, NULL, NIL, NULL, NULL);
}