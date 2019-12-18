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
 int MAXPGPATH ; 
 char* XLOGDIR ; 
 int /*<<< orphan*/  fatal_error (char*,...) ; 
 char* getenv (char*) ; 
 char* pg_strdup (char*) ; 
 scalar_t__ search_directory (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 

__attribute__((used)) static char *
identify_target_directory(char *directory, char *fname)
{
	char		fpath[MAXPGPATH];

	if (directory != NULL)
	{
		if (search_directory(directory, fname))
			return pg_strdup(directory);

		/* directory / XLOGDIR */
		snprintf(fpath, MAXPGPATH, "%s/%s", directory, XLOGDIR);
		if (search_directory(fpath, fname))
			return pg_strdup(fpath);
	}
	else
	{
		const char *datadir;

		/* current directory */
		if (search_directory(".", fname))
			return pg_strdup(".");
		/* XLOGDIR */
		if (search_directory(XLOGDIR, fname))
			return pg_strdup(XLOGDIR);

		datadir = getenv("PGDATA");
		/* $PGDATA / XLOGDIR */
		if (datadir != NULL)
		{
			snprintf(fpath, MAXPGPATH, "%s/%s", datadir, XLOGDIR);
			if (search_directory(fpath, fname))
				return pg_strdup(fpath);
		}
	}

	/* could not locate WAL file */
	if (fname)
		fatal_error("could not locate WAL file \"%s\"", fname);
	else
		fatal_error("could not find any WAL file");

	return NULL;				/* not reached */
}