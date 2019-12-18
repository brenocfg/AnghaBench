#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ss_currentScanDesc; } ;
struct TYPE_4__ {int tss_TidPtr; TYPE_2__ ss; scalar_t__ tss_NumTids; int /*<<< orphan*/ * tss_TidList; } ;
typedef  TYPE_1__ TidScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecScanReScan (TYPE_2__*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_rescan (scalar_t__,int /*<<< orphan*/ *) ; 

void
ExecReScanTidScan(TidScanState *node)
{
	if (node->tss_TidList)
		pfree(node->tss_TidList);
	node->tss_TidList = NULL;
	node->tss_NumTids = 0;
	node->tss_TidPtr = -1;

	/* not really necessary, but seems good form */
	if (node->ss.ss_currentScanDesc)
		table_rescan(node->ss.ss_currentScanDesc, NULL);

	ExecScanReScan(&node->ss);
}