#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int precise_ip; } ;
struct TYPE_4__ {TYPE_2__ attr; } ;
struct evsel {TYPE_1__ core; int /*<<< orphan*/  precise_max; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int ENOTSUP ; 
 int /*<<< orphan*/  display_attr (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug2 (char*,int,...) ; 
 int sys_perf_event_open (TYPE_2__*,int /*<<< orphan*/ ,int,int,unsigned long) ; 

__attribute__((used)) static int perf_event_open(struct evsel *evsel,
			   pid_t pid, int cpu, int group_fd,
			   unsigned long flags)
{
	int precise_ip = evsel->core.attr.precise_ip;
	int fd;

	while (1) {
		pr_debug2("sys_perf_event_open: pid %d  cpu %d  group_fd %d  flags %#lx",
			  pid, cpu, group_fd, flags);

		fd = sys_perf_event_open(&evsel->core.attr, pid, cpu, group_fd, flags);
		if (fd >= 0)
			break;

		/* Do not try less precise if not requested. */
		if (!evsel->precise_max)
			break;

		/*
		 * We tried all the precise_ip values, and it's
		 * still failing, so leave it to standard fallback.
		 */
		if (!evsel->core.attr.precise_ip) {
			evsel->core.attr.precise_ip = precise_ip;
			break;
		}

		pr_debug2("\nsys_perf_event_open failed, error %d\n", -ENOTSUP);
		evsel->core.attr.precise_ip--;
		pr_debug2("decreasing precise_ip by one (%d)\n", evsel->core.attr.precise_ip);
		display_attr(&evsel->core.attr);
	}

	return fd;
}