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
struct TYPE_3__ {int /*<<< orphan*/ * reader; int /*<<< orphan*/ * pei; } ;
typedef  TYPE_1__ GatherState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecParallelFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExecShutdownGatherWorkers(GatherState *node)
{
	if (node->pei != NULL)
		ExecParallelFinish(node->pei);

	/* Flush local copy of reader array */
	if (node->reader)
		pfree(node->reader);
	node->reader = NULL;
}