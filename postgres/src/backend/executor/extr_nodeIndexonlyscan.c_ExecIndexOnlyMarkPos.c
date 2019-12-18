#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * relsubs_done; int /*<<< orphan*/ ** relsubs_rowmark; int /*<<< orphan*/ ** relsubs_slot; } ;
struct TYPE_12__ {TYPE_6__* es_epq_active; } ;
struct TYPE_8__ {scalar_t__ plan; TYPE_5__* state; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/  ioss_ScanDesc; TYPE_2__ ss; } ;
struct TYPE_10__ {int scanrelid; } ;
typedef  TYPE_3__ Scan ;
typedef  TYPE_4__ IndexOnlyScanState ;
typedef  int Index ;
typedef  TYPE_5__ EState ;
typedef  TYPE_6__ EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  index_markpos (int /*<<< orphan*/ ) ; 

void
ExecIndexOnlyMarkPos(IndexOnlyScanState *node)
{
	EState	   *estate = node->ss.ps.state;
	EPQState   *epqstate = estate->es_epq_active;

	if (epqstate != NULL)
	{
		/*
		 * We are inside an EvalPlanQual recheck.  If a test tuple exists for
		 * this relation, then we shouldn't access the index at all.  We would
		 * instead need to save, and later restore, the state of the
		 * relsubs_done flag, so that re-fetching the test tuple is possible.
		 * However, given the assumption that no caller sets a mark at the
		 * start of the scan, we can only get here with relsubs_done[i]
		 * already set, and so no state need be saved.
		 */
		Index		scanrelid = ((Scan *) node->ss.ps.plan)->scanrelid;

		Assert(scanrelid > 0);
		if (epqstate->relsubs_slot[scanrelid - 1] != NULL ||
			epqstate->relsubs_rowmark[scanrelid - 1] != NULL)
		{
			/* Verify the claim above */
			if (!epqstate->relsubs_done[scanrelid - 1])
				elog(ERROR, "unexpected ExecIndexOnlyMarkPos call in EPQ recheck");
			return;
		}
	}

	index_markpos(node->ioss_ScanDesc);
}