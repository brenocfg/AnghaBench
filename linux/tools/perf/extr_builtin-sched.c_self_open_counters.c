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
struct rlimit {unsigned long rlim_cur; scalar_t__ rlim_max; } ;
struct perf_sched {unsigned long nr_tasks; scalar_t__ force; } ;
struct perf_event_attr {int /*<<< orphan*/  config; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  sbuf ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EMFILE ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  PERF_COUNT_SW_TASK_CLOCK ; 
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int STRERR_BUFSIZE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perf_event_open_cloexec_flag () ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,char*) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  str_error_r (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int self_open_counters(struct perf_sched *sched, unsigned long cur_task)
{
	struct perf_event_attr attr;
	char sbuf[STRERR_BUFSIZE], info[STRERR_BUFSIZE];
	int fd;
	struct rlimit limit;
	bool need_privilege = false;

	memset(&attr, 0, sizeof(attr));

	attr.type = PERF_TYPE_SOFTWARE;
	attr.config = PERF_COUNT_SW_TASK_CLOCK;

force_again:
	fd = sys_perf_event_open(&attr, 0, -1, -1,
				 perf_event_open_cloexec_flag());

	if (fd < 0) {
		if (errno == EMFILE) {
			if (sched->force) {
				BUG_ON(getrlimit(RLIMIT_NOFILE, &limit) == -1);
				limit.rlim_cur += sched->nr_tasks - cur_task;
				if (limit.rlim_cur > limit.rlim_max) {
					limit.rlim_max = limit.rlim_cur;
					need_privilege = true;
				}
				if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
					if (need_privilege && errno == EPERM)
						strcpy(info, "Need privilege\n");
				} else
					goto force_again;
			} else
				strcpy(info, "Have a try with -f option\n");
		}
		pr_err("Error: sys_perf_event_open() syscall returned "
		       "with %d (%s)\n%s", fd,
		       str_error_r(errno, sbuf, sizeof(sbuf)), info);
		exit(EXIT_FAILURE);
	}
	return fd;
}