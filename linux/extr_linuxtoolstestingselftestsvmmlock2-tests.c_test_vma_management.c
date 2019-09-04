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
struct vm_boundaries {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  KSFT_SKIP ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  MLOCK_ONFAULT ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ get_vm_area (unsigned long,struct vm_boundaries*) ; 
 unsigned long getpagesize () ; 
 scalar_t__ mlock2_ (void*,int,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munlock (void*,unsigned long) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int test_vma_management(bool call_mlock)
{
	int ret = 1;
	void *map;
	unsigned long page_size = getpagesize();
	struct vm_boundaries page1;
	struct vm_boundaries page2;
	struct vm_boundaries page3;

	map = mmap(NULL, 3 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (map == MAP_FAILED) {
		perror("mmap()");
		return ret;
	}

	if (call_mlock && mlock2_(map, 3 * page_size, MLOCK_ONFAULT)) {
		if (errno == ENOSYS) {
			printf("Cannot call new mlock family, skipping test\n");
			_exit(KSFT_SKIP);
		}
		perror("mlock(ONFAULT)\n");
		goto out;
	}

	if (get_vm_area((unsigned long)map, &page1) ||
	    get_vm_area((unsigned long)map + page_size, &page2) ||
	    get_vm_area((unsigned long)map + page_size * 2, &page3)) {
		printf("couldn't find mapping in /proc/self/maps\n");
		goto out;
	}

	/*
	 * Before we unlock a portion, we need to that all three pages are in
	 * the same VMA.  If they are not we abort this test (Note that this is
	 * not a failure)
	 */
	if (page1.start != page2.start || page2.start != page3.start) {
		printf("VMAs are not merged to start, aborting test\n");
		ret = 0;
		goto out;
	}

	if (munlock(map + page_size, page_size)) {
		perror("munlock()");
		goto out;
	}

	if (get_vm_area((unsigned long)map, &page1) ||
	    get_vm_area((unsigned long)map + page_size, &page2) ||
	    get_vm_area((unsigned long)map + page_size * 2, &page3)) {
		printf("couldn't find mapping in /proc/self/maps\n");
		goto out;
	}

	/* All three VMAs should be different */
	if (page1.start == page2.start || page2.start == page3.start) {
		printf("failed to split VMA for munlock\n");
		goto out;
	}

	/* Now unlock the first and third page and check the VMAs again */
	if (munlock(map, page_size * 3)) {
		perror("munlock()");
		goto out;
	}

	if (get_vm_area((unsigned long)map, &page1) ||
	    get_vm_area((unsigned long)map + page_size, &page2) ||
	    get_vm_area((unsigned long)map + page_size * 2, &page3)) {
		printf("couldn't find mapping in /proc/self/maps\n");
		goto out;
	}

	/* Now all three VMAs should be the same */
	if (page1.start != page2.start || page2.start != page3.start) {
		printf("failed to merge VMAs after munlock\n");
		goto out;
	}

	ret = 0;
out:
	munmap(map, 3 * page_size);
	return ret;
}