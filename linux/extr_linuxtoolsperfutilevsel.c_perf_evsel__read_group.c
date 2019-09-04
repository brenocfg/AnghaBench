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
typedef  int u64 ;
struct perf_stat_evsel {int* group_data; } ;
struct TYPE_2__ {int read_format; } ;
struct perf_evsel {TYPE_1__ attr; struct perf_stat_evsel* stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FD (struct perf_evsel*,int,int) ; 
 int PERF_FORMAT_ID ; 
 int errno ; 
 int /*<<< orphan*/  perf_evsel__is_group_leader (struct perf_evsel*) ; 
 int perf_evsel__process_group_data (struct perf_evsel*,int,int,int*) ; 
 int perf_evsel__read_size (struct perf_evsel*) ; 
 scalar_t__ readn (scalar_t__,int*,int) ; 
 int* zalloc (int) ; 

__attribute__((used)) static int
perf_evsel__read_group(struct perf_evsel *leader, int cpu, int thread)
{
	struct perf_stat_evsel *ps = leader->stats;
	u64 read_format = leader->attr.read_format;
	int size = perf_evsel__read_size(leader);
	u64 *data = ps->group_data;

	if (!(read_format & PERF_FORMAT_ID))
		return -EINVAL;

	if (!perf_evsel__is_group_leader(leader))
		return -EINVAL;

	if (!data) {
		data = zalloc(size);
		if (!data)
			return -ENOMEM;

		ps->group_data = data;
	}

	if (FD(leader, cpu, thread) < 0)
		return -EINVAL;

	if (readn(FD(leader, cpu, thread), data, size) <= 0)
		return -errno;

	return perf_evsel__process_group_data(leader, cpu, thread, data);
}