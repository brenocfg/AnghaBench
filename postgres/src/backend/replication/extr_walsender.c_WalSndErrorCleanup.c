#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ws_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  LWLockReleaseAll () ; 
 int /*<<< orphan*/ * MyReplicationSlot ; 
 int /*<<< orphan*/  ReplicationSlotCleanup () ; 
 int /*<<< orphan*/  ReplicationSlotRelease () ; 
 int /*<<< orphan*/  WALSNDSTATE_STARTUP ; 
 int /*<<< orphan*/  WalSndSetState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ got_SIGUSR2 ; 
 scalar_t__ got_STOPPING ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int replication_active ; 
 TYPE_1__* sendSeg ; 

void
WalSndErrorCleanup(void)
{
	LWLockReleaseAll();
	ConditionVariableCancelSleep();
	pgstat_report_wait_end();

	if (sendSeg->ws_file >= 0)
	{
		close(sendSeg->ws_file);
		sendSeg->ws_file = -1;
	}

	if (MyReplicationSlot != NULL)
		ReplicationSlotRelease();

	ReplicationSlotCleanup();

	replication_active = false;

	if (got_STOPPING || got_SIGUSR2)
		proc_exit(0);

	/* Revert back to startup state */
	WalSndSetState(WALSNDSTATE_STARTUP);
}