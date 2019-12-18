#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct target {int dummy; } ;
struct stat {int dummy; } ;
struct perf_thread_map {int nr; TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  procfs__mountpoint () ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  target__has_task (struct target*) ; 

__attribute__((used)) static bool is_target_alive(struct target *_target,
			    struct perf_thread_map *threads)
{
	struct stat st;
	int i;

	if (!target__has_task(_target))
		return true;

	for (i = 0; i < threads->nr; i++) {
		char path[PATH_MAX];

		scnprintf(path, PATH_MAX, "%s/%d", procfs__mountpoint(),
			  threads->map[i].pid);

		if (!stat(path, &st))
			return true;
	}

	return false;
}