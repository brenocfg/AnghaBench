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
 int MAP_ANONYMOUS ; 
 char* MAP_FAILED ; 
 int MAP_HUGETLB ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SIZE ; 
 char* mmap (void*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,void*) ; 

__attribute__((used)) static int test_body(void)
{
	void *addr;
	char *p;

	addr = (void *)0xa0000000;

	p = mmap(addr, SIZE, PROT_READ | PROT_WRITE,
		 MAP_HUGETLB | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (p != MAP_FAILED) {
		/*
		 * Typically the mmap will fail because no huge pages are
		 * allocated on the system. But if there are huge pages
		 * allocated the mmap will succeed. That's fine too, we just
		 * munmap here before continuing.  munmap() length of
		 * MAP_HUGETLB memory must be hugepage aligned.
		 */
		if (munmap(addr, SIZE)) {
			perror("munmap");
			return 1;
		}
	}

	p = mmap(addr, SIZE, PROT_READ | PROT_WRITE,
		 MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (p == MAP_FAILED) {
		printf("Mapping failed @ %p\n", addr);
		perror("mmap");
		return 1;
	}

	/*
	 * Either a user or kernel access is sufficient to trigger the bug.
	 * A kernel access is easier to spot & debug, as it will trigger the
	 * softlockup or RCU stall detectors, and when the system is kicked
	 * into xmon we get a backtrace in the kernel.
	 *
	 * A good option is:
	 *  getcwd(p, SIZE);
	 *
	 * For the purposes of this testcase it's preferable to spin in
	 * userspace, so the harness can kill us if we get stuck. That way we
	 * see a test failure rather than a dead system.
	 */
	*p = 0xf;

	munmap(addr, SIZE);

	return 0;
}