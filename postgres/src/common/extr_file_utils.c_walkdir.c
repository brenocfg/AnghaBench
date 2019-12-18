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
typedef  int /*<<< orphan*/  subpath ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int MAXPGPATH ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int lstat (char*,struct stat*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int stub1 (char const*,int) ; 
 int stub2 (char const*,int) ; 

__attribute__((used)) static void
walkdir(const char *path,
		int (*action) (const char *fname, bool isdir),
		bool process_symlinks)
{
	DIR		   *dir;
	struct dirent *de;

	dir = opendir(path);
	if (dir == NULL)
	{
		pg_log_error("could not open directory \"%s\": %m", path);
		return;
	}

	while (errno = 0, (de = readdir(dir)) != NULL)
	{
		char		subpath[MAXPGPATH * 2];
		struct stat fst;
		int			sret;

		if (strcmp(de->d_name, ".") == 0 ||
			strcmp(de->d_name, "..") == 0)
			continue;

		snprintf(subpath, sizeof(subpath), "%s/%s", path, de->d_name);

		if (process_symlinks)
			sret = stat(subpath, &fst);
		else
			sret = lstat(subpath, &fst);

		if (sret < 0)
		{
			pg_log_error("could not stat file \"%s\": %m", subpath);
			continue;
		}

		if (S_ISREG(fst.st_mode))
			(*action) (subpath, false);
		else if (S_ISDIR(fst.st_mode))
			walkdir(subpath, action, false);
	}

	if (errno)
		pg_log_error("could not read directory \"%s\": %m", path);

	(void) closedir(dir);

	/*
	 * It's important to fsync the destination directory itself as individual
	 * file fsyncs don't guarantee that the directory entry for the file is
	 * synced.  Recent versions of ext4 have made the window much wider but
	 * it's been an issue for ext3 and other filesystems in the past.
	 */
	(*action) (path, true);
}