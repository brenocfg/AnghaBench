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
struct stat {int st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  namebuf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 int S_IFDIR ; 
 scalar_t__ S_ISDIR (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  match_pat (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int rmdir (char const*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int unlink (char const*) ; 

__attribute__((used)) static int rm_rf_depth_pat(const char *path, int depth, const char **pat)
{
	DIR *dir;
	int ret;
	struct dirent *d;
	char namebuf[PATH_MAX];
	struct stat statbuf;

	/* Do not fail if there's no file. */
	ret = lstat(path, &statbuf);
	if (ret)
		return 0;

	/* Try to remove any file we get. */
	if (!(statbuf.st_mode & S_IFDIR))
		return unlink(path);

	/* We have directory in path. */
	dir = opendir(path);
	if (dir == NULL)
		return -1;

	while ((d = readdir(dir)) != NULL && !ret) {

		if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
			continue;

		if (!match_pat(d->d_name, pat)) {
			ret =  -2;
			break;
		}

		scnprintf(namebuf, sizeof(namebuf), "%s/%s",
			  path, d->d_name);

		/* We have to check symbolic link itself */
		ret = lstat(namebuf, &statbuf);
		if (ret < 0) {
			pr_debug("stat failed: %s\n", namebuf);
			break;
		}

		if (S_ISDIR(statbuf.st_mode))
			ret = depth ? rm_rf_depth_pat(namebuf, depth - 1, pat) : 0;
		else
			ret = unlink(namebuf);
	}
	closedir(dir);

	if (ret < 0)
		return ret;

	return rmdir(path);
}