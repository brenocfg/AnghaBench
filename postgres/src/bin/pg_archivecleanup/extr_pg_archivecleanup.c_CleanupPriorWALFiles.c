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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  WALFilePath ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ IsPartialXLogFileName (char*) ; 
 scalar_t__ IsXLogFileName (char*) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  TrimExtension (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  additional_ext ; 
 char* archiveLocation ; 
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ dryrun ; 
 int errno ; 
 scalar_t__ exclusiveCleanupFileName ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  pg_log_debug (char*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int unlink (char*) ; 

__attribute__((used)) static void
CleanupPriorWALFiles(void)
{
	int			rc;
	DIR		   *xldir;
	struct dirent *xlde;
	char		walfile[MAXPGPATH];

	if ((xldir = opendir(archiveLocation)) != NULL)
	{
		while (errno = 0, (xlde = readdir(xldir)) != NULL)
		{
			/*
			 * Truncation is essentially harmless, because we skip names of
			 * length other than XLOG_FNAME_LEN.  (In principle, one could use
			 * a 1000-character additional_ext and get trouble.)
			 */
			strlcpy(walfile, xlde->d_name, MAXPGPATH);
			TrimExtension(walfile, additional_ext);

			/*
			 * We ignore the timeline part of the XLOG segment identifiers in
			 * deciding whether a segment is still needed.  This ensures that
			 * we won't prematurely remove a segment from a parent timeline.
			 * We could probably be a little more proactive about removing
			 * segments of non-parent timelines, but that would be a whole lot
			 * more complicated.
			 *
			 * We use the alphanumeric sorting property of the filenames to
			 * decide which ones are earlier than the exclusiveCleanupFileName
			 * file. Note that this means files are not removed in the order
			 * they were originally written, in case this worries you.
			 */
			if ((IsXLogFileName(walfile) || IsPartialXLogFileName(walfile)) &&
				strcmp(walfile + 8, exclusiveCleanupFileName + 8) < 0)
			{
				char		WALFilePath[MAXPGPATH * 2]; /* the file path
														 * including archive */

				/*
				 * Use the original file name again now, including any
				 * extension that might have been chopped off before testing
				 * the sequence.
				 */
				snprintf(WALFilePath, sizeof(WALFilePath), "%s/%s",
						 archiveLocation, xlde->d_name);

				if (dryrun)
				{
					/*
					 * Prints the name of the file to be removed and skips the
					 * actual removal.  The regular printout is so that the
					 * user can pipe the output into some other program.
					 */
					printf("%s\n", WALFilePath);
					pg_log_debug("file \"%s\" would be removed", WALFilePath);
					continue;
				}

				pg_log_debug("removing file \"%s\"", WALFilePath);

				rc = unlink(WALFilePath);
				if (rc != 0)
				{
					pg_log_error("could not remove file \"%s\": %m",
								 WALFilePath);
					break;
				}
			}
		}

		if (errno)
			pg_log_error("could not read archive location \"%s\": %m",
						 archiveLocation);
		if (closedir(xldir))
			pg_log_error("could not close archive location \"%s\": %m",
						 archiveLocation);
	}
	else
		pg_log_error("could not open archive location \"%s\": %m",
					 archiveLocation);
}