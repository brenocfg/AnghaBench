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
typedef  int /*<<< orphan*/  srcbuffer ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  destbuffer ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  DIRECTORY_LOCK_FILE ; 
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  LOG ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WAIT_EVENT_LOCK_FILE_ADDTODATADIR_READ ; 
 int /*<<< orphan*/  WAIT_EVENT_LOCK_FILE_ADDTODATADIR_SYNC ; 
 int /*<<< orphan*/  WAIT_EVENT_LOCK_FILE_ADDTODATADIR_WRITE ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_fsync (int) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ write (int,char*,int) ; 

void
AddToDataDirLockFile(int target_line, const char *str)
{
	int			fd;
	int			len;
	int			lineno;
	char	   *srcptr;
	char	   *destptr;
	char		srcbuffer[BLCKSZ];
	char		destbuffer[BLCKSZ];

	fd = open(DIRECTORY_LOCK_FILE, O_RDWR | PG_BINARY, 0);
	if (fd < 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m",
						DIRECTORY_LOCK_FILE)));
		return;
	}
	pgstat_report_wait_start(WAIT_EVENT_LOCK_FILE_ADDTODATADIR_READ);
	len = read(fd, srcbuffer, sizeof(srcbuffer) - 1);
	pgstat_report_wait_end();
	if (len < 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not read from file \"%s\": %m",
						DIRECTORY_LOCK_FILE)));
		close(fd);
		return;
	}
	srcbuffer[len] = '\0';

	/*
	 * Advance over lines we are not supposed to rewrite, then copy them to
	 * destbuffer.
	 */
	srcptr = srcbuffer;
	for (lineno = 1; lineno < target_line; lineno++)
	{
		char	   *eol = strchr(srcptr, '\n');

		if (eol == NULL)
			break;				/* not enough lines in file yet */
		srcptr = eol + 1;
	}
	memcpy(destbuffer, srcbuffer, srcptr - srcbuffer);
	destptr = destbuffer + (srcptr - srcbuffer);

	/*
	 * Fill in any missing lines before the target line, in case lines are
	 * added to the file out of order.
	 */
	for (; lineno < target_line; lineno++)
	{
		if (destptr < destbuffer + sizeof(destbuffer))
			*destptr++ = '\n';
	}

	/*
	 * Write or rewrite the target line.
	 */
	snprintf(destptr, destbuffer + sizeof(destbuffer) - destptr, "%s\n", str);
	destptr += strlen(destptr);

	/*
	 * If there are more lines in the old file, append them to destbuffer.
	 */
	if ((srcptr = strchr(srcptr, '\n')) != NULL)
	{
		srcptr++;
		snprintf(destptr, destbuffer + sizeof(destbuffer) - destptr, "%s",
				 srcptr);
	}

	/*
	 * And rewrite the data.  Since we write in a single kernel call, this
	 * update should appear atomic to onlookers.
	 */
	len = strlen(destbuffer);
	errno = 0;
	pgstat_report_wait_start(WAIT_EVENT_LOCK_FILE_ADDTODATADIR_WRITE);
	if (lseek(fd, (off_t) 0, SEEK_SET) != 0 ||
		(int) write(fd, destbuffer, len) != len)
	{
		pgstat_report_wait_end();
		/* if write didn't set errno, assume problem is no disk space */
		if (errno == 0)
			errno = ENOSPC;
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not write to file \"%s\": %m",
						DIRECTORY_LOCK_FILE)));
		close(fd);
		return;
	}
	pgstat_report_wait_end();
	pgstat_report_wait_start(WAIT_EVENT_LOCK_FILE_ADDTODATADIR_SYNC);
	if (pg_fsync(fd) != 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not write to file \"%s\": %m",
						DIRECTORY_LOCK_FILE)));
	}
	pgstat_report_wait_end();
	if (close(fd) != 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not write to file \"%s\": %m",
						DIRECTORY_LOCK_FILE)));
	}
}