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
typedef  int /*<<< orphan*/  CommandId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  IsParallelWorker () ; 
 int /*<<< orphan*/  currentCommandId ; 
 int currentCommandIdUsed ; 

CommandId
GetCurrentCommandId(bool used)
{
	/* this is global to a transaction, not subtransaction-local */
	if (used)
	{
		/*
		 * Forbid setting currentCommandIdUsed in a parallel worker, because
		 * we have no provision for communicating this back to the master.  We
		 * could relax this restriction when currentCommandIdUsed was already
		 * true at the start of the parallel operation.
		 */
		Assert(!IsParallelWorker());
		currentCommandIdUsed = true;
	}
	return currentCommandId;
}