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
 int /*<<< orphan*/  MAXPGPATH ; 
#define  RESTORE_COMMAND_COPY 129 
#define  RESTORE_COMMAND_LINK 128 
 int /*<<< orphan*/  SET_RESTORE_COMMAND (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WALFilePath ; 
 char* archiveLocation ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* nextWALFileName ; 
 char* progname ; 
 int restoreCommandType ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ stat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_buf ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xlogFilePath ; 

__attribute__((used)) static void
CustomizableInitialize(void)
{
#ifdef WIN32
	snprintf(WALFilePath, MAXPGPATH, "%s\\%s", archiveLocation, nextWALFileName);
	switch (restoreCommandType)
	{
		case RESTORE_COMMAND_LINK:
			SET_RESTORE_COMMAND("mklink", WALFilePath, xlogFilePath);
			break;
		case RESTORE_COMMAND_COPY:
		default:
			SET_RESTORE_COMMAND("copy", WALFilePath, xlogFilePath);
			break;
	}
#else
	snprintf(WALFilePath, MAXPGPATH, "%s/%s", archiveLocation, nextWALFileName);
	switch (restoreCommandType)
	{
		case RESTORE_COMMAND_LINK:
#ifdef HAVE_WORKING_LINK
			SET_RESTORE_COMMAND("ln -s -f", WALFilePath, xlogFilePath);
			break;
#endif
		case RESTORE_COMMAND_COPY:
		default:
			SET_RESTORE_COMMAND("cp", WALFilePath, xlogFilePath);
			break;
	}
#endif

	/*
	 * This code assumes that archiveLocation is a directory You may wish to
	 * add code to check for tape libraries, etc.. So, since it is a
	 * directory, we use stat to test if it's accessible
	 */
	if (stat(archiveLocation, &stat_buf) != 0)
	{
		fprintf(stderr, "%s: archive location \"%s\" does not exist\n", progname, archiveLocation);
		fflush(stderr);
		exit(2);
	}
}