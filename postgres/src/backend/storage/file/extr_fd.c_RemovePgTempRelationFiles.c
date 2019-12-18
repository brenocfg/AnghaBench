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
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int MAXPGPATH ; 
 struct dirent* ReadDirExtended (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemovePgTempRelationFilesInDbspace (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strspn (char*,char*) ; 

__attribute__((used)) static void
RemovePgTempRelationFiles(const char *tsdirname)
{
	DIR		   *ts_dir;
	struct dirent *de;
	char		dbspace_path[MAXPGPATH * 2];

	ts_dir = AllocateDir(tsdirname);

	while ((de = ReadDirExtended(ts_dir, tsdirname, LOG)) != NULL)
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
		RemovePgTempRelationFilesInDbspace(dbspace_path);
	}

	FreeDir(ts_dir);
}