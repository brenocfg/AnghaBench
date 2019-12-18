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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  VirtualTransactionId ;
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  ProcSignalReason ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 scalar_t__ CancelVirtualTransaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  STANDBY_INITIAL_WAIT_US ; 
 scalar_t__ TimestampDifferenceExceeds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VirtualTransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualXactLock (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WaitExceedsMaxStandbyDelay () ; 
 char* get_ps_display (int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  set_ps_display (char*,int) ; 
 int /*<<< orphan*/  standbyWait_us ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ update_process_title ; 

__attribute__((used)) static void
ResolveRecoveryConflictWithVirtualXIDs(VirtualTransactionId *waitlist,
									   ProcSignalReason reason)
{
	TimestampTz waitStart;
	char	   *new_status;

	/* Fast exit, to avoid a kernel call if there's no work to be done. */
	if (!VirtualTransactionIdIsValid(*waitlist))
		return;

	waitStart = GetCurrentTimestamp();
	new_status = NULL;			/* we haven't changed the ps display */

	while (VirtualTransactionIdIsValid(*waitlist))
	{
		/* reset standbyWait_us for each xact we wait for */
		standbyWait_us = STANDBY_INITIAL_WAIT_US;

		/* wait until the virtual xid is gone */
		while (!VirtualXactLock(*waitlist, false))
		{
			/*
			 * Report via ps if we have been waiting for more than 500 msec
			 * (should that be configurable?)
			 */
			if (update_process_title && new_status == NULL &&
				TimestampDifferenceExceeds(waitStart, GetCurrentTimestamp(),
										   500))
			{
				const char *old_status;
				int			len;

				old_status = get_ps_display(&len);
				new_status = (char *) palloc(len + 8 + 1);
				memcpy(new_status, old_status, len);
				strcpy(new_status + len, " waiting");
				set_ps_display(new_status, false);
				new_status[len] = '\0'; /* truncate off " waiting" */
			}

			/* Is it time to kill it? */
			if (WaitExceedsMaxStandbyDelay())
			{
				pid_t		pid;

				/*
				 * Now find out who to throw out of the balloon.
				 */
				Assert(VirtualTransactionIdIsValid(*waitlist));
				pid = CancelVirtualTransaction(*waitlist, reason);

				/*
				 * Wait a little bit for it to die so that we avoid flooding
				 * an unresponsive backend when system is heavily loaded.
				 */
				if (pid != 0)
					pg_usleep(5000L);
			}
		}

		/* The virtual transaction is gone now, wait for the next one */
		waitlist++;
	}

	/* Reset ps display if we changed it */
	if (new_status)
	{
		set_ps_display(new_status, false);
		pfree(new_status);
	}
}