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
struct dirent {int d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char* CPU_PATH ; 
 int DT_DIR ; 
 int /*<<< orphan*/  F_OK ; 
 int LEN_MAX ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_cpu_dscr_default (char*,unsigned long) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_all_cpu_dscr_defaults(unsigned long val)
{
	DIR *sysfs;
	struct dirent *dp;
	char file[LEN_MAX];

	sysfs = opendir(CPU_PATH);
	if (!sysfs) {
		perror("opendir() failed");
		return 1;
	}

	while ((dp = readdir(sysfs))) {
		int len;

		if (!(dp->d_type & DT_DIR))
			continue;
		if (!strcmp(dp->d_name, "cpuidle"))
			continue;
		if (!strstr(dp->d_name, "cpu"))
			continue;

		len = snprintf(file, LEN_MAX, "%s%s/dscr", CPU_PATH, dp->d_name);
		if (len >= LEN_MAX)
			continue;
		if (access(file, F_OK))
			continue;

		if (check_cpu_dscr_default(file, val))
			return 1;
	}
	closedir(sysfs);
	return 0;
}