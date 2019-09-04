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
struct perf_pmu_alias {int snapshot; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int perf_pmu__parse_snapshot(struct perf_pmu_alias *alias,
				    char *dir, char *name)
{
	char path[PATH_MAX];
	int fd;

	scnprintf(path, PATH_MAX, "%s/%s.snapshot", dir, name);

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return -1;

	alias->snapshot = true;
	close(fd);
	return 0;
}