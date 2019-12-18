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
struct perf_event_attr {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ store_event (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int,unsigned long) ; 

void test_attr__open(struct perf_event_attr *attr, pid_t pid, int cpu,
		     int fd, int group_fd, unsigned long flags)
{
	int errno_saved = errno;

	if ((fd != -1) && store_event(attr, pid, cpu, fd, group_fd, flags)) {
		pr_err("test attr FAILED");
		exit(128);
	}

	errno = errno_saved;
}