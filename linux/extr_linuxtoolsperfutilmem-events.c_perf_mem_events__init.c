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
struct stat {int dummy; } ;
struct perf_mem_event {int supported; int /*<<< orphan*/  sysfs_name; } ;

/* Variables and functions */
 int ENOENT ; 
 int PATH_MAX ; 
 int PERF_MEM_EVENTS__MAX ; 
 struct perf_mem_event* perf_mem_events ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 char* sysfs__mount () ; 

int perf_mem_events__init(void)
{
	const char *mnt = sysfs__mount();
	bool found = false;
	int j;

	if (!mnt)
		return -ENOENT;

	for (j = 0; j < PERF_MEM_EVENTS__MAX; j++) {
		char path[PATH_MAX];
		struct perf_mem_event *e = &perf_mem_events[j];
		struct stat st;

		scnprintf(path, PATH_MAX, "%s/devices/cpu/events/%s",
			  mnt, e->sysfs_name);

		if (!stat(path, &st))
			e->supported = found = true;
	}

	return found ? 0 : -ENOENT;
}