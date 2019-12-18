#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * queryDesc; } ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  EndCopy (TYPE_1__*) ; 
 int /*<<< orphan*/  ExecutorEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecutorFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeQueryDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 

__attribute__((used)) static void
EndCopyTo(CopyState cstate)
{
	if (cstate->queryDesc != NULL)
	{
		/* Close down the query and free resources. */
		ExecutorFinish(cstate->queryDesc);
		ExecutorEnd(cstate->queryDesc);
		FreeQueryDesc(cstate->queryDesc);
		PopActiveSnapshot();
	}

	/* Clean up storage */
	EndCopy(cstate);
}