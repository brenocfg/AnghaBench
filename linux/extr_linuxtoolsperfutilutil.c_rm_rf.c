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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  namebuf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int lstat (char*,struct stat*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int rmdir (char const*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int unlink (char*) ; 

int rm_rf(const char *path)
{
	DIR *dir;
	int ret = 0;
	struct dirent *d;
	char namebuf[PATH_MAX];

	dir = opendir(path);
	if (dir == NULL)
		return 0;

	while ((d = readdir(dir)) != NULL && !ret) {
		struct stat statbuf;

		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
			continue;

		scnprintf(namebuf, sizeof(namebuf), "%s/%s",
			  path, d->d_name);

		/* We have to check symbolic link itself */
		ret = lstat(namebuf, &statbuf);
		if (ret < 0) {
			pr_debug("stat failed: %s\n", namebuf);
			break;
		}

		if (S_ISDIR(statbuf.st_mode))
			ret = rm_rf(namebuf);
		else
			ret = unlink(namebuf);
	}
	closedir(dir);

	if (ret < 0)
		return ret;

	return rmdir(path);
}