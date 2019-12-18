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
typedef  int /*<<< orphan*/  XLogSegNo ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TimeLineID ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG3 ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetOldestRestartPoint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  StrNCpy (char*,char*,int) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XLByteToSeg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogFileName (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int system (char*) ; 
 scalar_t__ wait_result_is_any_signal (int,int) ; 
 int /*<<< orphan*/  wait_result_to_str (int) ; 
 int /*<<< orphan*/  wal_segment_size ; 

void
ExecuteRecoveryCommand(const char *command, const char *commandName, bool failOnSignal)
{
	char		xlogRecoveryCmd[MAXPGPATH];
	char		lastRestartPointFname[MAXPGPATH];
	char	   *dp;
	char	   *endp;
	const char *sp;
	int			rc;
	XLogSegNo	restartSegNo;
	XLogRecPtr	restartRedoPtr;
	TimeLineID	restartTli;

	Assert(command && commandName);

	/*
	 * Calculate the archive file cutoff point for use during log shipping
	 * replication. All files earlier than this point can be deleted from the
	 * archive, though there is no requirement to do so.
	 */
	GetOldestRestartPoint(&restartRedoPtr, &restartTli);
	XLByteToSeg(restartRedoPtr, restartSegNo, wal_segment_size);
	XLogFileName(lastRestartPointFname, restartTli, restartSegNo,
				 wal_segment_size);

	/*
	 * construct the command to be executed
	 */
	dp = xlogRecoveryCmd;
	endp = xlogRecoveryCmd + MAXPGPATH - 1;
	*endp = '\0';

	for (sp = command; *sp; sp++)
	{
		if (*sp == '%')
		{
			switch (sp[1])
			{
				case 'r':
					/* %r: filename of last restartpoint */
					sp++;
					StrNCpy(dp, lastRestartPointFname, endp - dp);
					dp += strlen(dp);
					break;
				case '%':
					/* convert %% to a single % */
					sp++;
					if (dp < endp)
						*dp++ = *sp;
					break;
				default:
					/* otherwise treat the % as not special */
					if (dp < endp)
						*dp++ = *sp;
					break;
			}
		}
		else
		{
			if (dp < endp)
				*dp++ = *sp;
		}
	}
	*dp = '\0';

	ereport(DEBUG3,
			(errmsg_internal("executing %s \"%s\"", commandName, command)));

	/*
	 * execute the constructed command
	 */
	rc = system(xlogRecoveryCmd);
	if (rc != 0)
	{
		/*
		 * If the failure was due to any sort of signal, it's best to punt and
		 * abort recovery.  See comments in RestoreArchivedFile().
		 */
		ereport((failOnSignal && wait_result_is_any_signal(rc, true)) ? FATAL : WARNING,
		/*------
		   translator: First %s represents a postgresql.conf parameter name like
		  "recovery_end_command", the 2nd is the value of that parameter, the
		  third an already translated error message. */
				(errmsg("%s \"%s\": %s", commandName,
						command, wait_result_to_str(rc))));
	}
}