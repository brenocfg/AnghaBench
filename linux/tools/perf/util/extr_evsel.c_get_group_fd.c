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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
struct evsel {TYPE_1__ core; struct evsel* leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int FD (struct evsel*,int,int) ; 
 scalar_t__ perf_evsel__is_group_leader (struct evsel*) ; 

__attribute__((used)) static int get_group_fd(struct evsel *evsel, int cpu, int thread)
{
	struct evsel *leader = evsel->leader;
	int fd;

	if (perf_evsel__is_group_leader(evsel))
		return -1;

	/*
	 * Leader must be already processed/open,
	 * if not it's a bug.
	 */
	BUG_ON(!leader->core.fd);

	fd = FD(leader, cpu, thread);
	BUG_ON(fd == -1);

	return fd;
}