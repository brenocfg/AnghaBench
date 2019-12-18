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
typedef  int TimeLineID ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateFile (char*,char*) ; 
 scalar_t__ ArchiveRecoveryRequested ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  FreeFile (int /*<<< orphan*/ *) ; 
 int MAXFNAMELEN ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  RestoreArchivedFile (char*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLHistoryFileName (char*,int) ; 
 int /*<<< orphan*/  TLHistoryFilePath (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 

bool
existsTimeLineHistory(TimeLineID probeTLI)
{
	char		path[MAXPGPATH];
	char		histfname[MAXFNAMELEN];
	FILE	   *fd;

	/* Timeline 1 does not have a history file, so no need to check */
	if (probeTLI == 1)
		return false;

	if (ArchiveRecoveryRequested)
	{
		TLHistoryFileName(histfname, probeTLI);
		RestoreArchivedFile(path, histfname, "RECOVERYHISTORY", 0, false);
	}
	else
		TLHistoryFilePath(path, probeTLI);

	fd = AllocateFile(path, "r");
	if (fd != NULL)
	{
		FreeFile(fd);
		return true;
	}
	else
	{
		if (errno != ENOENT)
			ereport(FATAL,
					(errcode_for_file_access(),
					 errmsg("could not open file \"%s\": %m", path)));
		return false;
	}
}