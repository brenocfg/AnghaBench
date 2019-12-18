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

/* Variables and functions */
 int MAP_FILE ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_NONE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  fail (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* mmap (void*,int const,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int main(void)
{
	const int PAGE_SIZE = sysconf(_SC_PAGESIZE);
	const unsigned long va_max = 1UL << 32;
	unsigned long va;
	void *p;
	int fd;
	unsigned long a, b;

	fd = open("/dev/zero", O_RDONLY);
	if (fd == -1)
		return 1;

	for (va = 0; va < va_max; va += PAGE_SIZE) {
		p = mmap((void *)va, PAGE_SIZE, PROT_NONE, MAP_PRIVATE|MAP_FILE|MAP_FIXED, fd, 0);
		if (p == (void *)va)
			break;
	}
	if (va == va_max) {
		fprintf(stderr, "error: mmap doesn't like you\n");
		return 1;
	}

	a = (unsigned long)p;
	b = (unsigned long)p + PAGE_SIZE;

	pass("/proc/self/map_files/%lx-%lx", a, b);
	fail("/proc/self/map_files/ %lx-%lx", a, b);
	fail("/proc/self/map_files/%lx -%lx", a, b);
	fail("/proc/self/map_files/%lx- %lx", a, b);
	fail("/proc/self/map_files/%lx-%lx ", a, b);
	fail("/proc/self/map_files/0%lx-%lx", a, b);
	fail("/proc/self/map_files/%lx-0%lx", a, b);
	if (sizeof(long) == 4) {
		fail("/proc/self/map_files/100000000%lx-%lx", a, b);
		fail("/proc/self/map_files/%lx-100000000%lx", a, b);
	} else if (sizeof(long) == 8) {
		fail("/proc/self/map_files/10000000000000000%lx-%lx", a, b);
		fail("/proc/self/map_files/%lx-10000000000000000%lx", a, b);
	} else
		return 1;

	return 0;
}