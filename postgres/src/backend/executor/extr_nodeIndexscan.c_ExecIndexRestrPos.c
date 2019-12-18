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
struct TYPE_11__ {int /*<<< orphan*/  iss_ScanDesc; TYPE_2__ ss; } ;
struct TYPE_10__ {int scanrelid; } ;
typedef  TYPE_3__ Scan ;
typedef  TYPE_4__ IndexScanState ;
typedef  int Index ;
typedef  TYPE_5__ EState ;
typedef  TYPE_6__ EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  index_restrpos (int /*<<< orphan*/ ) ; 

void
ExecIndexRestrPos(IndexScanState *node)
{
	EState	   *estate = node->ss.ps.state;
	EPQState   *epqstate = estate->es_epq_active;

	if (estate->es_epq_active != NULL)
	{
		/* See comments in ExecIndexMarkPos */
		Index		scanrelid = ((Scan *) node->ss.ps.plan)->scanrelid;

		Assert(scanrelid > 0);
		if (epqstate->relsubs_slot[scanrelid - 1] != NULL ||
			epqstate->relsubs_rowmark[scanrelid - 1] != NULL)
		{
			/* Verify the claim above */
			if (!epqstate->relsubs_done[scanrelid - 1])
				elog(ERROR, "unexpected ExecIndexRestrPos call in EPQ recheck");
			return;
		}
	}

	index_restrpos(node->iss_ScanDesc);
}