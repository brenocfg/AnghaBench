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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * FALLBACK_PROMOTE_SIGNAL_FILE ; 
 scalar_t__ IsPromoteTriggered () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/ * PROMOTE_SIGNAL_FILE ; 
 int /*<<< orphan*/ * PromoteTriggerFile ; 
 int /*<<< orphan*/  ResetPromoteTriggered () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 int fast_promote ; 
 scalar_t__ stat (int /*<<< orphan*/ *,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
CheckForStandbyTrigger(void)
{
	struct stat stat_buf;
	static bool triggered = false;

	if (triggered)
		return true;

	if (IsPromoteTriggered())
	{
		/*
		 * In 9.1 and 9.2 the postmaster unlinked the promote file inside the
		 * signal handler. It now leaves the file in place and lets the
		 * Startup process do the unlink. This allows Startup to know whether
		 * it should create a full checkpoint before starting up (fallback
		 * mode). Fast promotion takes precedence.
		 */
		if (stat(PROMOTE_SIGNAL_FILE, &stat_buf) == 0)
		{
			unlink(PROMOTE_SIGNAL_FILE);
			unlink(FALLBACK_PROMOTE_SIGNAL_FILE);
			fast_promote = true;
		}
		else if (stat(FALLBACK_PROMOTE_SIGNAL_FILE, &stat_buf) == 0)
		{
			unlink(FALLBACK_PROMOTE_SIGNAL_FILE);
			fast_promote = false;
		}

		ereport(LOG, (errmsg("received promote request")));

		ResetPromoteTriggered();
		triggered = true;
		return true;
	}

	if (PromoteTriggerFile == NULL || strcmp(PromoteTriggerFile, "") == 0)
		return false;

	if (stat(PromoteTriggerFile, &stat_buf) == 0)
	{
		ereport(LOG,
				(errmsg("promote trigger file found: %s", PromoteTriggerFile)));
		unlink(PromoteTriggerFile);
		triggered = true;
		fast_promote = true;
		return true;
	}
	else if (errno != ENOENT)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not stat promote trigger file \"%s\": %m",
						PromoteTriggerFile)));

	return false;
}