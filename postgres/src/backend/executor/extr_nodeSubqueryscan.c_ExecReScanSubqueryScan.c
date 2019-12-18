#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_9__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_8__ {TYPE_3__* subplan; TYPE_4__ ss; } ;
typedef  TYPE_2__ SubqueryScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (TYPE_3__*) ; 
 int /*<<< orphan*/  ExecScanReScan (TYPE_4__*) ; 
 int /*<<< orphan*/  UpdateChangedParamSet (TYPE_3__*,int /*<<< orphan*/ *) ; 

void
ExecReScanSubqueryScan(SubqueryScanState *node)
{
	ExecScanReScan(&node->ss);

	/*
	 * ExecReScan doesn't know about my subplan, so I have to do
	 * changed-parameter signaling myself.  This is just as well, because the
	 * subplan has its own memory context in which its chgParam state lives.
	 */
	if (node->ss.ps.chgParam != NULL)
		UpdateChangedParamSet(node->subplan, node->ss.ps.chgParam);

	/*
	 * if chgParam of subnode is not null then plan will be re-scanned by
	 * first ExecProcNode.
	 */
	if (node->subplan->chgParam == NULL)
		ExecReScan(node->subplan);
}