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

/* Variables and functions */
 int /*<<< orphan*/  DestroyParallelContext (int) ; 
 int ParallelContext ; 
 int /*<<< orphan*/  WARNING ; 
 int dlist_head_element (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  node ; 
 int pcxt ; 
 int /*<<< orphan*/  pcxt_list ; 

void
AtEOXact_Parallel(bool isCommit)
{
	while (!dlist_is_empty(&pcxt_list))
	{
		ParallelContext *pcxt;

		pcxt = dlist_head_element(ParallelContext, node, &pcxt_list);
		if (isCommit)
			elog(WARNING, "leaked parallel context");
		DestroyParallelContext(pcxt);
	}
}