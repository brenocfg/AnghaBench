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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {scalar_t__ plan; } ;
struct TYPE_8__ {int /*<<< orphan*/  scanrelid; } ;
struct TYPE_7__ {TYPE_4__ ps; TYPE_1__* ss_ScanTupleSlot; } ;
struct TYPE_6__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_2__ ScanState ;
typedef  TYPE_3__ Scan ;

/* Variables and functions */
 int /*<<< orphan*/  ExecConditionalAssignProjectionInfo (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ExecAssignScanProjectionInfo(ScanState *node)
{
	Scan	   *scan = (Scan *) node->ps.plan;
	TupleDesc	tupdesc = node->ss_ScanTupleSlot->tts_tupleDescriptor;

	ExecConditionalAssignProjectionInfo(&node->ps, tupdesc, scan->scanrelid);
}