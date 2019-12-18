#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_stat_evsel {int* group_data; } ;
struct TYPE_3__ {int read_format; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; struct perf_stat_evsel* stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FD (struct evsel*,int,int) ; 
 int PERF_FORMAT_ID ; 
 int errno ; 
 int /*<<< orphan*/  perf_evsel__is_group_leader (struct evsel*) ; 
 int perf_evsel__process_group_data (struct evsel*,int,int,int*) ; 
 int perf_evsel__read_size (TYPE_2__*) ; 
 scalar_t__ readn (scalar_t__,int*,int) ; 
 int* zalloc (int) ; 

__attribute__((used)) static int
perf_evsel__read_group(struct evsel *leader, int cpu, int thread)
{
	struct perf_stat_evsel *ps = leader->stats;
	u64 read_format = leader->core.attr.read_format;
	int size = perf_evsel__read_size(&leader->core);
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