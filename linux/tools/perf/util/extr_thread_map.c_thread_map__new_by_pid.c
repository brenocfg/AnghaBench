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
struct perf_thread_map {int nr; int /*<<< orphan*/  refcnt; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter ; 
 int /*<<< orphan*/  free (struct dirent**) ; 
 int /*<<< orphan*/  perf_thread_map__set_pid (struct perf_thread_map*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int scandir (char*,struct dirent***,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct perf_thread_map* thread_map__alloc (int) ; 
 int /*<<< orphan*/  zfree (struct dirent**) ; 

struct perf_thread_map *thread_map__new_by_pid(pid_t pid)
{
	struct perf_thread_map *threads;
	char name[256];
	int items;
	struct dirent **namelist = NULL;
	int i;

	sprintf(name, "/proc/%d/task", pid);
	items = scandir(name, &namelist, filter, NULL);
	if (items <= 0)
		return NULL;

	threads = thread_map__alloc(items);
	if (threads != NULL) {
		for (i = 0; i < items; i++)
			perf_thread_map__set_pid(threads, i, atoi(namelist[i]->d_name));
		threads->nr = items;
		refcount_set(&threads->refcnt, 1);
	}

	for (i=0; i<items; i++)
		zfree(&namelist[i]);
	free(namelist);

	return threads;
}