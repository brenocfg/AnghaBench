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
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MakePGDirectory (char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 

void
PathNameCreateTemporaryDir(const char *basedir, const char *directory)
{
	if (MakePGDirectory(directory) < 0)
	{
		if (errno == EEXIST)
			return;

		/*
		 * Failed.  Try to create basedir first in case it's missing. Tolerate
		 * EEXIST to close a race against another process following the same
		 * algorithm.
		 */
		if (MakePGDirectory(basedir) < 0 && errno != EEXIST)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("cannot create temporary directory \"%s\": %m",
							basedir)));

		/* Try again. */
		if (MakePGDirectory(directory) < 0 && errno != EEXIST)
			ereport(ERROR,
					(errcode_for_file_access(),
					 errmsg("cannot create temporary subdirectory \"%s\": %m",
							directory)));
	}
}