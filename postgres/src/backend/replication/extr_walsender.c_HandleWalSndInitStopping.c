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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyProcPid ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  am_walsender ; 
 int got_STOPPING ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replication_active ; 

void
HandleWalSndInitStopping(void)
{
	Assert(am_walsender);

	/*
	 * If replication has not yet started, die like with SIGTERM. If
	 * replication is active, only set a flag and wake up the main loop. It
	 * will send any outstanding WAL, wait for it to be replicated to the
	 * standby, and then exit gracefully.
	 */
	if (!replication_active)
		kill(MyProcPid, SIGTERM);
	else
		got_STOPPING = true;
}