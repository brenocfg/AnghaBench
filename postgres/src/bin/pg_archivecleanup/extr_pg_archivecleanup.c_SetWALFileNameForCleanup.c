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
typedef  int uint32 ;

/* Variables and functions */
 scalar_t__ IsBackupHistoryFileName (int /*<<< orphan*/ ) ; 
 scalar_t__ IsPartialXLogFileName (int /*<<< orphan*/ ) ; 
 scalar_t__ IsXLogFileName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TrimExtension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogFileNameById (int /*<<< orphan*/ ,int,int,int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  additional_ext ; 
 int /*<<< orphan*/  exclusiveCleanupFileName ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  restartWALFileName ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*,int*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SetWALFileNameForCleanup(void)
{
	bool		fnameOK = false;

	TrimExtension(restartWALFileName, additional_ext);

	/*
	 * If restartWALFileName is a WAL file name then just use it directly. If
	 * restartWALFileName is a .partial or .backup filename, make sure we use
	 * the prefix of the filename, otherwise we will remove wrong files since
	 * 000000010000000000000010.partial and
	 * 000000010000000000000010.00000020.backup are after
	 * 000000010000000000000010.
	 */
	if (IsXLogFileName(restartWALFileName))
	{
		strcpy(exclusiveCleanupFileName, restartWALFileName);
		fnameOK = true;
	}
	else if (IsPartialXLogFileName(restartWALFileName))
	{
		int			args;
		uint32		tli = 1,
					log = 0,
					seg = 0;

		args = sscanf(restartWALFileName, "%08X%08X%08X.partial",
					  &tli, &log, &seg);
		if (args == 3)
		{
			fnameOK = true;

			/*
			 * Use just the prefix of the filename, ignore everything after
			 * first period
			 */
			XLogFileNameById(exclusiveCleanupFileName, tli, log, seg);
		}
	}
	else if (IsBackupHistoryFileName(restartWALFileName))
	{
		int			args;
		uint32		tli = 1,
					log = 0,
					seg = 0,
					offset = 0;

		args = sscanf(restartWALFileName, "%08X%08X%08X.%08X.backup", &tli, &log, &seg, &offset);
		if (args == 4)
		{
			fnameOK = true;

			/*
			 * Use just the prefix of the filename, ignore everything after
			 * first period
			 */
			XLogFileNameById(exclusiveCleanupFileName, tli, log, seg);
		}
	}

	if (!fnameOK)
	{
		pg_log_error("invalid file name argument");
		fprintf(stderr, _("Try \"%s --help\" for more information.\n"), progname);
		exit(2);
	}
}