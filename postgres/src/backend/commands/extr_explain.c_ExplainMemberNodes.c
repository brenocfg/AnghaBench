#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExplainPropertyInteger (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ExplainMemberNodes(PlanState **planstates, int nsubnodes, int nplans,
				   List *ancestors, ExplainState *es)
{
	int			j;

	/*
	 * The number of subnodes being lower than the number of subplans that was
	 * specified in the plan means that some subnodes have been ignored per
	 * instruction for the partition pruning code during the executor
	 * initialization.  To make this a bit less mysterious, we'll indicate
	 * here that this has happened.
	 */
	if (nsubnodes < nplans)
		ExplainPropertyInteger("Subplans Removed", NULL, nplans - nsubnodes, es);

	for (j = 0; j < nsubnodes; j++)
		ExplainNode(planstates[j], ancestors,
					"Member", NULL, es);
}