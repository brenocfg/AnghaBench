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
 int /*<<< orphan*/  ClearPendingActionsAndNotifies () ; 
 scalar_t__ NIL ; 
 scalar_t__ amRegisteredListener ; 
 int /*<<< orphan*/  asyncQueueUnregister () ; 
 scalar_t__ listenChannels ; 

void
AtAbort_Notify(void)
{
	/*
	 * If we LISTEN but then roll back the transaction after PreCommit_Notify,
	 * we have registered as a listener but have not made any entry in
	 * listenChannels.  In that case, deregister again.
	 */
	if (amRegisteredListener && listenChannels == NIL)
		asyncQueueUnregister();

	/* And clean up */
	ClearPendingActionsAndNotifies();
}