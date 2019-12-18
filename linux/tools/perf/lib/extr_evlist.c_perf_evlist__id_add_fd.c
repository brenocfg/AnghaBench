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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int read_format; } ;
struct perf_evsel {TYPE_1__ attr; } ;
struct perf_evlist {int dummy; } ;
typedef  int /*<<< orphan*/  read_data ;

/* Variables and functions */
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ID ; 
 int PERF_FORMAT_GROUP ; 
 int PERF_FORMAT_ID ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 scalar_t__ errno ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_evlist__id_add (struct perf_evlist*,struct perf_evsel*,int,int,int /*<<< orphan*/ ) ; 
 int perf_evlist__read_format (struct perf_evlist*) ; 
 int read (int,int /*<<< orphan*/ **,int) ; 

int perf_evlist__id_add_fd(struct perf_evlist *evlist,
			   struct perf_evsel *evsel,
			   int cpu, int thread, int fd)
{
	u64 read_data[4] = { 0, };
	int id_idx = 1; /* The first entry is the counter value */
	u64 id;
	int ret;

	ret = ioctl(fd, PERF_EVENT_IOC_ID, &id);
	if (!ret)
		goto add;

	if (errno != ENOTTY)
		return -1;

	/* Legacy way to get event id.. All hail to old kernels! */

	/*
	 * This way does not work with group format read, so bail
	 * out in that case.
	 */
	if (perf_evlist__read_format(evlist) & PERF_FORMAT_GROUP)
		return -1;

	if (!(evsel->attr.read_format & PERF_FORMAT_ID) ||
	    read(fd, &read_data, sizeof(read_data)) == -1)
		return -1;

	if (evsel->attr.read_format & PERF_FORMAT_TOTAL_TIME_ENABLED)
		++id_idx;
	if (evsel->attr.read_format & PERF_FORMAT_TOTAL_TIME_RUNNING)
		++id_idx;

	id = read_data[id_idx];

add:
	perf_evlist__id_add(evlist, evsel, cpu, thread, id);
	return 0;
}