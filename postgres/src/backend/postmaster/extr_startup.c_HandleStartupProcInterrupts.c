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
 scalar_t__ IsUnderPostmaster ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  PostmasterIsAlive () ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int got_SIGHUP ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 scalar_t__ shutdown_requested ; 

void
HandleStartupProcInterrupts(void)
{
	/*
	 * Check if we were requested to re-read config file.
	 */
	if (got_SIGHUP)
	{
		got_SIGHUP = false;
		ProcessConfigFile(PGC_SIGHUP);
	}

	/*
	 * Check if we were requested to exit without finishing recovery.
	 */
	if (shutdown_requested)
		proc_exit(1);

	/*
	 * Emergency bailout if postmaster has died.  This is to avoid the
	 * necessity for manual cleanup of all postmaster children.
	 */
	if (IsUnderPostmaster && !PostmasterIsAlive())
		exit(1);
}