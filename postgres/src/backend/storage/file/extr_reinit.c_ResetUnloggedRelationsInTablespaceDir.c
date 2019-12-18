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
typedef  int /*<<< orphan*/  dbspace_path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int MAXPGPATH ; 
 struct dirent* ReadDir (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ResetUnloggedRelationsInDbspaceDir (char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

__attribute__((used)) static void
ResetUnloggedRelationsInTablespaceDir(const char *tsdirname, int op)
{
	DIR		   *ts_dir;
	struct dirent *de;
	char		dbspace_path[MAXPGPATH * 2];

	ts_dir = AllocateDir(tsdirname);

	/*
	 * If we get ENOENT on a tablespace directory, log it and return.  This
	 * can happen if a previous DROP TABLESPACE crashed between removing the
	 * tablespace directory and removing the symlink in pg_tblspc.  We don't
	 * really want to prevent database startup in that scenario, so let it
	 * pass instead.  Any other type of error will be reported by ReadDir
	 * (causing a startup failure).
	 */
	if (ts_dir == NULL && errno == ENOENT)
	{
		ereport(LOG,
				(errcode_for_file_access(),
				 errmsg("could not open directory \"%s\": %m",
						tsdirname)));
		return;
	}

	while ((de = ReadDir(ts_dir, tsdirname)) != NULL)
	{
		/*
		 * We're only interested in the per-database directories, which have
		 * numeric names.  Note that this code will also (properly) ignore "."
		 * and "..".
		 */
		if (strspn(de->d_name, "0123456789") != strlen(de->d_name))
			continue;

		snprintf(dbspace_path, sizeof(dbspace_path), "%s/%s",
				 tsdirname, de->d_name);
		ResetUnloggedRelationsInDbspaceDir(dbspace_path, op);
	}

	FreeDir(ts_dir);
}