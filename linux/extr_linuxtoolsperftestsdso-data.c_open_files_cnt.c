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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  procfs__mountpoint () ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static long open_files_cnt(void)
{
	char path[PATH_MAX];
	struct dirent *dent;
	DIR *dir;
	long nr = 0;

	scnprintf(path, PATH_MAX, "%s/self/fd", procfs__mountpoint());
	pr_debug("fd path: %s\n", path);

	dir = opendir(path);
	TEST_ASSERT_VAL("failed to open fd directory", dir);

	while ((dent = readdir(dir)) != NULL) {
		if (!strcmp(dent->d_name, ".") ||
		    !strcmp(dent->d_name, ".."))
			continue;

		nr++;
	}

	closedir(dir);
	return nr - 1;
}