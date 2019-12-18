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
 scalar_t__ CloseTransientFile (int) ; 
 scalar_t__ EACCES ; 
 int O_RDONLY ; 
 int OpenTransientFile (char const*,int) ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pg_flush_data (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pre_sync_fname(const char *fname, bool isdir, int elevel)
{
	int			fd;

	/* Don't try to flush directories, it'll likely just fail */
	if (isdir)
		return;

	fd = OpenTransientFile(fname, O_RDONLY | PG_BINARY);

	if (fd < 0)
	{
		if (errno == EACCES)
			return;
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not open file \"%s\": %m", fname)));
		return;
	}

	/*
	 * pg_flush_data() ignores errors, which is ok because this is only a
	 * hint.
	 */
	pg_flush_data(fd, 0, 0);

	if (CloseTransientFile(fd) != 0)
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not close file \"%s\": %m", fname)));
}