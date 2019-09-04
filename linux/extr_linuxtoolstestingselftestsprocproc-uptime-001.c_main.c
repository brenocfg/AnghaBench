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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_uptime (int,int*,int*) ; 

int main(void)
{
	uint64_t start, u0, u1, i0, i1;
	int fd;

	fd = open("/proc/uptime", O_RDONLY);
	assert(fd >= 0);

	proc_uptime(fd, &u0, &i0);
	start = u0;
	do {
		proc_uptime(fd, &u1, &i1);
		assert(u1 >= u0);
		assert(i1 >= i0);
		u0 = u1;
		i0 = i1;
	} while (u1 - start < 100);

	return 0;
}