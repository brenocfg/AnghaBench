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
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  ReportTemporaryFileUsage (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int errno ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ unlink (char const*) ; 

bool
PathNameDeleteTemporaryFile(const char *path, bool error_on_failure)
{
	struct stat filestats;
	int			stat_errno;

	/* Get the final size for pgstat reporting. */
	if (stat(path, &filestats) != 0)
		stat_errno = errno;
	else
		stat_errno = 0;

	/*
	 * Unlike FileClose's automatic file deletion code, we tolerate
	 * non-existence to support BufFileDeleteShared which doesn't know how
	 * many segments it has to delete until it runs out.
	 */
	if (stat_errno == ENOENT)
		return false;

	if (unlink(path) < 0)
	{
		if (errno != ENOENT)
			ereport(error_on_failure ? ERROR : LOG,
					(errcode_for_file_access(),
					 errmsg("could not unlink temporary file \"%s\": %m",
							path)));
		return false;
	}

	if (stat_errno == 0)
		ReportTemporaryFileUsage(path, filestats.st_size);
	else
	{
		errno = stat_errno;
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not stat file \"%s\": %m", path)));
	}

	return true;
}