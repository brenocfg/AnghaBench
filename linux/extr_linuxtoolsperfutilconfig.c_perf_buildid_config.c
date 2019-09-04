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
 int MAXPATHLEN ; 
 char* buildid_dir ; 
 char* perf_config_dirname (char const*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int perf_buildid_config(const char *var, const char *value)
{
	/* same dir for all commands */
	if (!strcmp(var, "buildid.dir")) {
		const char *dir = perf_config_dirname(var, value);

		if (!dir) {
			pr_err("Invalid buildid directory!\n");
			return -1;
		}
		strncpy(buildid_dir, dir, MAXPATHLEN-1);
		buildid_dir[MAXPATHLEN-1] = '\0';
	}

	return 0;
}