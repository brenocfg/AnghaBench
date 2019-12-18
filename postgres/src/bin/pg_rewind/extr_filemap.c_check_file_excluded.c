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
typedef  int /*<<< orphan*/  localpath ;

/* Variables and functions */
 int MAXPGPATH ; 
 char** excludeDirContents ; 
 int /*<<< orphan*/ ** excludeFiles ; 
 char* last_dir_separator (char const*) ; 
 int /*<<< orphan*/  pg_log_debug (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 char const* strstr (char const*,char*) ; 

__attribute__((used)) static bool
check_file_excluded(const char *path, bool is_source)
{
	char		localpath[MAXPGPATH];
	int			excludeIdx;
	const char *filename;

	/* check individual files... */
	for (excludeIdx = 0; excludeFiles[excludeIdx] != NULL; excludeIdx++)
	{
		filename = last_dir_separator(path);
		if (filename == NULL)
			filename = path;
		else
			filename++;
		if (strcmp(filename, excludeFiles[excludeIdx]) == 0)
		{
			if (is_source)
				pg_log_debug("entry \"%s\" excluded from source file list",
							 path);
			else
				pg_log_debug("entry \"%s\" excluded from target file list",
							 path);
			return true;
		}
	}

	/*
	 * ... And check some directories.  Note that this includes any contents
	 * within the directories themselves.
	 */
	for (excludeIdx = 0; excludeDirContents[excludeIdx] != NULL; excludeIdx++)
	{
		snprintf(localpath, sizeof(localpath), "%s/",
				 excludeDirContents[excludeIdx]);
		if (strstr(path, localpath) == path)
		{
			if (is_source)
				pg_log_debug("entry \"%s\" excluded from source file list",
							 path);
			else
				pg_log_debug("entry \"%s\" excluded from target file list",
							 path);
			return true;
		}
	}

	return false;
}