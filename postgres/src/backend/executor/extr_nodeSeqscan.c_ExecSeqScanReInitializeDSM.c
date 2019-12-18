#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ss_currentRelation; TYPE_1__* ss_currentScanDesc; } ;
struct TYPE_7__ {TYPE_2__ ss; } ;
struct TYPE_5__ {int /*<<< orphan*/  rs_parallel; } ;
typedef  TYPE_3__ SeqScanState ;
typedef  int /*<<< orphan*/  ParallelTableScanDesc ;
typedef  int /*<<< orphan*/  ParallelContext ;

/* Variables and functions */
 int /*<<< orphan*/  table_parallelscan_reinitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ExecSeqScanReInitializeDSM(SeqScanState *node,
						   ParallelContext *pcxt)
{
	ParallelTableScanDesc pscan;

	pscan = node->ss.ss_currentScanDesc->rs_parallel;
	table_parallelscan_reinitialize(node->ss.ss_currentRelation, pscan);
}