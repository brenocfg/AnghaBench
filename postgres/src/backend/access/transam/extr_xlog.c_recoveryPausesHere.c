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
 int /*<<< orphan*/  HandleStartupProcInterrupts () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LocalHotStandbyActive ; 
 scalar_t__ RecoveryIsPaused () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

__attribute__((used)) static void
recoveryPausesHere(void)
{
	/* Don't pause unless users can connect! */
	if (!LocalHotStandbyActive)
		return;

	ereport(LOG,
			(errmsg("recovery has paused"),
			 errhint("Execute pg_wal_replay_resume() to continue.")));

	while (RecoveryIsPaused())
	{
		pg_usleep(1000000L);	/* 1000 ms */
		HandleStartupProcInterrupts();
	}
}