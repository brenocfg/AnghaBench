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
struct perf_evlist {int nr_mmaps; TYPE_1__* overwrite_mmap; } ;
struct TYPE_2__ {int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_EVENT_IOC_PAUSE_OUTPUT ; 
 int ioctl (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int perf_evlist__set_paused(struct perf_evlist *evlist, bool value)
{
	int i;

	if (!evlist->overwrite_mmap)
		return 0;

	for (i = 0; i < evlist->nr_mmaps; i++) {
		int fd = evlist->overwrite_mmap[i].fd;
		int err;

		if (fd < 0)
			continue;
		err = ioctl(fd, PERF_EVENT_IOC_PAUSE_OUTPUT, value ? 1 : 0);
		if (err)
			return err;
	}
	return 0;
}