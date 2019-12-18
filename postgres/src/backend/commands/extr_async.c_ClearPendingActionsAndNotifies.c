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
 int /*<<< orphan*/ * pendingActions ; 
 int /*<<< orphan*/ * pendingNotifies ; 

__attribute__((used)) static void
ClearPendingActionsAndNotifies(void)
{
	/*
	 * Everything's allocated in either TopTransactionContext or the context
	 * for the subtransaction to which it corresponds. So, there's nothing
	 * to do here except rest the pointers; the space will be reclaimed when
	 * the contexts are deleted.
	 */
	pendingActions = NULL;
	pendingNotifies = NULL;
}