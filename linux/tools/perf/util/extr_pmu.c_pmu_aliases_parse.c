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
struct list_head {int dummy; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EINVAL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ perf_pmu__new_alias (struct list_head*,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ pmu_alias_info_file (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int pmu_aliases_parse(char *dir, struct list_head *head)
{
	struct dirent *evt_ent;
	DIR *event_dir;

	event_dir = opendir(dir);
	if (!event_dir)
		return -EINVAL;

	while ((evt_ent = readdir(event_dir))) {
		char path[PATH_MAX];
		char *name = evt_ent->d_name;
		FILE *file;

		if (!strcmp(name, ".") || !strcmp(name, ".."))
			continue;

		/*
		 * skip info files parsed in perf_pmu__new_alias()
		 */
		if (pmu_alias_info_file(name))
			continue;

		scnprintf(path, PATH_MAX, "%s/%s", dir, name);

		file = fopen(path, "r");
		if (!file) {
			pr_debug("Cannot open %s\n", path);
			continue;
		}

		if (perf_pmu__new_alias(head, dir, name, file) < 0)
			pr_debug("Cannot set up %s\n", name);
		fclose(file);
	}

	closedir(event_dir);
	return 0;
}