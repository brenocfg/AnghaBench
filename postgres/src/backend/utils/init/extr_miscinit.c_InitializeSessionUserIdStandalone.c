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
 int /*<<< orphan*/  AssertState (int) ; 
 int /*<<< orphan*/  AuthenticatedUserId ; 
 int AuthenticatedUserIsSuperuser ; 
 int /*<<< orphan*/  BOOTSTRAP_SUPERUSERID ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 scalar_t__ IsBackgroundWorker ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSessionUserId (int /*<<< orphan*/ ,int) ; 

void
InitializeSessionUserIdStandalone(void)
{
	/*
	 * This function should only be called in single-user mode, in autovacuum
	 * workers, and in background workers.
	 */
	AssertState(!IsUnderPostmaster || IsAutoVacuumWorkerProcess() || IsBackgroundWorker);

	/* call only once */
	AssertState(!OidIsValid(AuthenticatedUserId));

	AuthenticatedUserId = BOOTSTRAP_SUPERUSERID;
	AuthenticatedUserIsSuperuser = true;

	SetSessionUserId(BOOTSTRAP_SUPERUSERID, true);
}