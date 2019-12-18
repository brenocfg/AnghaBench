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
struct perf_event_attr {int disabled; int bp_type; int bp_len; int exclude_user; scalar_t__ bp_addr; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  attr ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int DAWR_LENGTH_MAX ; 
 int HW_BREAKPOINT_R ; 
 int HW_BREAKPOINT_W ; 
 int MAX_LOOPS ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_DISABLE ; 
 int /*<<< orphan*/  PERF_EVENT_IOC_ENABLE ; 
 int /*<<< orphan*/  PERF_TYPE_BREAKPOINT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long long,unsigned long long,int,int,int) ; 
 int rand () ; 
 size_t read (int,unsigned long long*,int) ; 
 int sys_perf_event_open (struct perf_event_attr*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int runtestsingle(int readwriteflag, int exclude_user, int arraytest)
{
	int i,j;
	struct perf_event_attr attr;
	size_t res;
	unsigned long long breaks, needed;
	int readint;
	int readintarraybig[2*DAWR_LENGTH_MAX/sizeof(int)];
	int *readintalign;
	volatile int *ptr;
	int break_fd;
	int loop_num = MAX_LOOPS - (rand() % 100); /* provide some variability */
	volatile int *k;

	/* align to 0x400 boundary as required by DAWR */
	readintalign = (int *)(((unsigned long)readintarraybig + 0x7ff) &
			       0xfffffffffffff800);

	ptr = &readint;
	if (arraytest)
		ptr = &readintalign[0];

	/* setup counters */
	memset(&attr, 0, sizeof(attr));
	attr.disabled = 1;
	attr.type = PERF_TYPE_BREAKPOINT;
	attr.bp_type = readwriteflag;
	attr.bp_addr = (__u64)ptr;
	attr.bp_len = sizeof(int);
	if (arraytest)
		attr.bp_len = DAWR_LENGTH_MAX;
	attr.exclude_user = exclude_user;
	break_fd = sys_perf_event_open(&attr, 0, -1, -1, 0);
	if (break_fd < 0) {
		perror("sys_perf_event_open");
		exit(1);
	}

	/* start counters */
	ioctl(break_fd, PERF_EVENT_IOC_ENABLE);

	/* Test a bunch of reads and writes */
	k = &readint;
	for (i = 0; i < loop_num; i++) {
		if (arraytest)
			k = &(readintalign[i % (DAWR_LENGTH_MAX/sizeof(int))]);

		j = *k;
		*k = j;
	}

	/* stop counters */
	ioctl(break_fd, PERF_EVENT_IOC_DISABLE);

	/* read and check counters */
	res = read(break_fd, &breaks, sizeof(unsigned long long));
	assert(res == sizeof(unsigned long long));
	/* we read and write each loop, so subtract the ones we are counting */
	needed = 0;
	if (readwriteflag & HW_BREAKPOINT_R)
		needed += loop_num;
	if (readwriteflag & HW_BREAKPOINT_W)
		needed += loop_num;
	needed = needed * (1 - exclude_user);
	printf("TESTED: addr:0x%lx brks:% 8lld loops:% 8i rw:%i !user:%i array:%i\n",
	       (unsigned long int)ptr, breaks, loop_num, readwriteflag, exclude_user, arraytest);
	if (breaks != needed) {
		printf("FAILED: 0x%lx brks:%lld needed:%lli %i %i %i\n\n",
		       (unsigned long int)ptr, breaks, needed, loop_num, readwriteflag, exclude_user);
		return 1;
	}
	close(break_fd);

	return 0;
}