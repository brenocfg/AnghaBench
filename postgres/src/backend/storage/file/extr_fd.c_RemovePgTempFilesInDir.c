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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  rm_path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/ * AllocateDir (char const*) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FreeDir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_TEMP_FILE_PREFIX ; 
 struct dirent* ReadDirExtended (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlink (char*) ; 

void
RemovePgTempFilesInDir(const char *tmpdirname, bool missing_ok, bool unlink_all)
{
	DIR		   *temp_dir;
	struct dirent *temp_de;
	char		rm_path[MAXPGPATH * 2];

	temp_dir = AllocateDir(tmpdirname);

	if (temp_dir == NULL && errno == ENOENT && missing_ok)
		return;

	while ((temp_de = ReadDirExtended(temp_dir, tmpdirname, LOG)) != NULL)
	{
		if (strcmp(temp_de->d_name, ".") == 0 ||
			strcmp(temp_de->d_name, "..") == 0)
			continue;

		snprintf(rm_path, sizeof(rm_path), "%s/%s",
				 tmpdirname, temp_de->d_name);

		if (unlink_all ||
			strncmp(temp_de->d_name,
					PG_TEMP_FILE_PREFIX,
					strlen(PG_TEMP_FILE_PREFIX)) == 0)
		{
			struct stat statbuf;

			if (lstat(rm_path, &statbuf) < 0)
			{
				ereport(LOG,
						(errcode_for_file_access(),
						 errmsg("could not stat file \"%s\": %m", rm_path)));
				continue;
			}

			if (S_ISDIR(statbuf.st_mode))
			{
				/* recursively remove contents, then directory itself */
				RemovePgTempFilesInDir(rm_path, false, true);

				if (rmdir(rm_path) < 0)
					ereport(LOG,
							(errcode_for_file_access(),
							 errmsg("could not remove directory \"%s\": %m",
									rm_path)));
			}
			else
			{
				if (unlink(rm_path) < 0)
					ereport(LOG,
							(errcode_for_file_access(),
							 errmsg("could not remove file \"%s\": %m",
									rm_path)));
			}
		}
		else
			ereport(LOG,
					(errmsg("unexpected file found in temporary-files directory: \"%s\"",
							rm_path)));
	}

	FreeDir(temp_dir);
}