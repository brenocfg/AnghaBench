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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (unsigned long*) ; 
 unsigned long* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,unsigned int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_uptime (int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  sys_sched_getaffinity (int /*<<< orphan*/ ,unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  sys_sched_setaffinity (int /*<<< orphan*/ ,unsigned int,unsigned long*) ; 

int main(void)
{
	unsigned int len;
	unsigned long *m;
	unsigned int cpu;
	uint64_t u0, u1, i0, i1;
	int fd;

	/* find out "nr_cpu_ids" */
	m = NULL;
	len = 0;
	do {
		len += sizeof(unsigned long);
		free(m);
		m = malloc(len);
	} while (sys_sched_getaffinity(0, len, m) == -EINVAL);

	fd = open("/proc/uptime", O_RDONLY);
	assert(fd >= 0);

	proc_uptime(fd, &u0, &i0);
	for (cpu = 0; cpu < len * 8; cpu++) {
		memset(m, 0, len);
		m[cpu / (8 * sizeof(unsigned long))] |= 1UL << (cpu % (8 * sizeof(unsigned long)));

		/* CPU might not exist, ignore error */
		sys_sched_setaffinity(0, len, m);

		proc_uptime(fd, &u1, &i1);
		assert(u1 >= u0);
		assert(i1 >= i0);
		u0 = u1;
		i0 = i1;
	}

	return 0;
}