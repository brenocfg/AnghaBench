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
 scalar_t__ ENOENT ; 
 int O_RDWR ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fsync (int) ; 
 scalar_t__ fsync_fname (char const*,int) ; 
 scalar_t__ fsync_parent_path (char const*) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,...) ; 
 scalar_t__ rename (char const*,char const*) ; 

int
durable_rename(const char *oldfile, const char *newfile)
{
	int			fd;

	/*
	 * First fsync the old and target path (if it exists), to ensure that they
	 * are properly persistent on disk. Syncing the target file is not
	 * strictly necessary, but it makes it easier to reason about crashes;
	 * because it's then guaranteed that either source or target file exists
	 * after a crash.
	 */
	if (fsync_fname(oldfile, false) != 0)
		return -1;

	fd = open(newfile, PG_BINARY | O_RDWR, 0);
	if (fd < 0)
	{
		if (errno != ENOENT)
		{
			pg_log_error("could not open file \"%s\": %m", newfile);
			return -1;
		}
	}
	else
	{
		if (fsync(fd) != 0)
		{
			pg_log_error("could not fsync file \"%s\": %m", newfile);
			close(fd);
			return -1;
		}
		close(fd);
	}

	/* Time to do the real deal... */
	if (rename(oldfile, newfile) != 0)
	{
		pg_log_error("could not rename file \"%s\" to \"%s\": %m",
					 oldfile, newfile);
		return -1;
	}

	/*
	 * To guarantee renaming the file is persistent, fsync the file with its
	 * new name, and its containing directory.
	 */
	if (fsync_fname(newfile, false) != 0)
		return -1;

	if (fsync_parent_path(newfile) != 0)
		return -1;

	return 0;
}