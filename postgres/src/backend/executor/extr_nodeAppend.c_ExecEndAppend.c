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
struct TYPE_3__ {int as_nplans; int /*<<< orphan*/ ** appendplans; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_1__ AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ *) ; 

void
ExecEndAppend(AppendState *node)
{
	PlanState **appendplans;
	int			nplans;
	int			i;

	/*
	 * get information from the node
	 */
	appendplans = node->appendplans;
	nplans = node->as_nplans;

	/*
	 * shut down each of the subscans
	 */
	for (i = 0; i < nplans; i++)
		ExecEndNode(appendplans[i]);
}