#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int begun; int done; int haveblock; int /*<<< orphan*/  ss; scalar_t__ donetuples; } ;
typedef  TYPE_1__ SampleScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecScanReScan (int /*<<< orphan*/ *) ; 

void
ExecReScanSampleScan(SampleScanState *node)
{
	/* Remember we need to do BeginSampleScan again (if we did it at all) */
	node->begun = false;
	node->done = false;
	node->haveblock = false;
	node->donetuples = 0;

	ExecScanReScan(&node->ss);
}