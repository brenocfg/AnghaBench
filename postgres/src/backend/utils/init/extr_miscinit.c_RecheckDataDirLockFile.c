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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  DIRECTORY_LOCK_FILE ; 
#define  ENOENT 129 
#define  ENOTDIR 128 
 int /*<<< orphan*/  LOG ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  WAIT_EVENT_LOCK_FILE_RECHECKDATADIR_READ ; 
 long atol (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int errno ; 
 long getpid () ; 
 int open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

bool
RecheckDataDirLockFile(void)
{
	int			fd;
	int			len;
	long		file_pid;
	char		buffer[BLCKSZ];

	fd = open(DIRECTORY_LOCK_FILE, O_RDWR | PG_BINARY, 0);
	if (fd < 0)
	{
		/*
		 * There are many foreseeable false-positive error conditions.  For
		 * safety, fail only on enumerated clearly-something-is-wrong
		 * conditions.
		 */
		switch (errno)
		{
			case ENOENT:
			case ENOTDIR:
				/* disaster */
				ereport(LOG,
						(errcode_for_file_access(),
						 errmsg("could not open file \"%s\": %m",
								DIRECTORY_LOCK_FILE)));
				return false;
			default:
				/* non-fatal, at least for now */
				ereport(LOG,
						(errcode_for_file_access(),
						 errmsg("could not open file \"%s\": %m; continuing anyway",
								DIRECTORY_LOCK_FILE)));
				return true;
		}
	}
	pgstat_report_wait_start(WAIT_EVENT_LOCK_FILE_RECHECKDATADIR_READ);
	len = read(fd, buffer, sizeof(buffer) - 1);
	pgstat_report_wait_end();
	if (len < 0)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not read from file \"%s\": %m",
						DIRECTORY_LOCK_FILE)));
		close(fd);
		return true;			/* treat read failure as nonfatal */
	}
	buffer[len] = '\0';
	close(fd);
	file_pid = atol(buffer);
	if (file_pid == getpid())
		return true;			/* all is well */

	/* Trouble: someone's overwritten the lock file */
	ereport(LOG,
			(errmsg("lock file \"%s\" contains wrong PID: %ld instead of %ld",
					DIRECTORY_LOCK_FILE, file_pid, (long) getpid())));
	return false;
}